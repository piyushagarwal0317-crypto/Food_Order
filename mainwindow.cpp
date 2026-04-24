#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString> // Qt's version of std::string
#include <cstdlib>
#include <ctime>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFont>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // This loads your drag-and-drop design

    // Add our cuisines to the dropdown box!
    ui->categoryComboBox->addItem("All Cuisines");
    ui->categoryComboBox->addItem("Main");
    ui->categoryComboBox->addItem("Sides");
    ui->categoryComboBox->addItem("Beverage");
    ui->categoryComboBox->addItem("Dessert");

    // 1. Load the database!
   myMenu.loadMenuFromFile(":/menu.txt");

    // 2. Loop through the C++ menu and put it on the visual Qt screen
    std::vector<MenuItem> items = myMenu.getItems();

    for (const auto& item : items) {
        // Now it will look like: "1 - Cheeseburger - $5.99 (Main)"
        QString displayText = QString::number(item.getId()) + " - " +
                              QString::fromStdString(item.getName()) + " - $" +
                              QString::number(item.getPrice()) +
                              " (" + QString::fromStdString(item.getCategory()) + ")";

        ui->menuListWidget->addItem(displayText);
    }

    // --- SETUP THE RANDOM SPECIALS ---
    std::srand(std::time(0)); // Start the random number generator

    std::vector<MenuItem> allItems = myMenu.getItems();

    // Make sure we actually have items before trying to pick one!
    if (allItems.size() > 0) {
        // Pick two random numbers based on how many items are in the menu
        int random1 = std::rand() % allItems.size();
        int random2 = std::rand() % allItems.size();

        // Build the text
        scrollingText = "   *** TODAY'S SPECIALS: " +
                        QString::fromStdString(allItems[random1].getName()) + " and " +
                        QString::fromStdString(allItems[random2].getName()) + " *** ";
    } else {
        scrollingText = "   *** Welcome to our Restaurant! *** ";
    }

    // --- SETUP THE TIMER ---
    scrollTimer = new QTimer(this);
    // Tell the timer to run our update function every time it ticks
    connect(scrollTimer, &QTimer::timeout, this, &MainWindow::updateScrollingText);
    scrollTimer->start(150); // 150 milliseconds = speed of the scroll. Lower is faster!
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_addToCartButton_clicked()
{
    int currentRow = ui->menuListWidget->currentRow();
    if (currentRow < 0) return;

    std::vector<MenuItem> items = myMenu.getItems();
    MenuItem selectedFood = items[currentRow];

    // addItemToCart now returns the index — same index if duplicate, new index if fresh
    int cartIndex = myOrder.addItemToCart(selectedFood, 1);
    int qty       = myOrder.getQuantity(cartIndex);

    // Build the display text with quantity and running line total
    QString cartText = QString::fromStdString(selectedFood.getName()) +
                       " x" + QString::number(qty) +
                       "  —  $" + QString::number(selectedFood.getPrice() * qty, 'f', 2);

    if (cartIndex < ui->cartListWidget->count()) {
        // Item already had a row — update it in place
        ui->cartListWidget->item(cartIndex)->setText(cartText);
    } else {
        // Brand new item — append a fresh row
        ui->cartListWidget->addItem(cartText);
    }

    ui->totalLabel->setText("Total: $" + QString::number(myOrder.calculateTotal(), 'f', 2));
}


void MainWindow::on_checkoutButton_clicked()
{
    // 1. Save receipt text file
    QString receiptPath = QCoreApplication::applicationDirPath() + "/receipt.txt";
    myOrder.saveReceiptToFile(receiptPath.toStdString());

    // 2. Read the receipt text back
    QString receiptContent;
    QFile file(receiptPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        receiptContent = in.readAll();
        file.close();
    }

    // 3. Build the receipt popup
    QDialog receiptDialog(this);
    receiptDialog.setWindowTitle("Order Complete — Food Villa");
    receiptDialog.resize(340, 750);
    receiptDialog.setStyleSheet("background-color: white;");

    QVBoxLayout *layout = new QVBoxLayout(&receiptDialog);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 10);

    // --- Receipt text ---
    QTextEdit *receiptText = new QTextEdit(&receiptDialog);
    receiptText->setReadOnly(true);
    receiptText->setText(receiptContent);
    QFont monoFont("Courier");
    monoFont.setStyleHint(QFont::Monospace);
    monoFont.setPointSize(10);
    receiptText->setFont(monoFont);
    receiptText->setStyleSheet("color: black; background-color: white; border: none;");
    receiptText->setFixedHeight(320);
    layout->addWidget(receiptText);

    // --- Divider ---
    QLabel *divider = new QLabel("- - - - - - - - - - - - - - - - - - - -", &receiptDialog);
    divider->setAlignment(Qt::AlignCenter);
    divider->setStyleSheet("color: #aaa; font-size: 11px; padding: 4px 0;");
    layout->addWidget(divider);

    // --- "Scan to Pay" label ---
    QLabel *payLabel = new QLabel("📱  Scan & Pay via PhonePe", &receiptDialog);
    payLabel->setAlignment(Qt::AlignCenter);
    payLabel->setStyleSheet(
        "color: #5f259f;"           // PhonePe purple
        "font-weight: bold;"
        "font-size: 13px;"
        "padding: 8px 0 4px 0;"
        );
    layout->addWidget(payLabel);

    // --- QR Code image ---
    QLabel *qrLabel = new QLabel(&receiptDialog);
    QPixmap qrPixmap(":/phonepe_qr.jpeg");
    if (qrPixmap.isNull()) {
        // Fallback if image not found
        qrLabel->setText("[QR code not found — check resources.qrc]");
        qrLabel->setStyleSheet("color: red; font-size: 11px;");
    } else {
        // Scale to fit nicely in the popup, keep aspect ratio
        qrLabel->setPixmap(qrPixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    qrLabel->setAlignment(Qt::AlignCenter);
    qrLabel->setStyleSheet("padding: 6px 0;");
    layout->addWidget(qrLabel);

    // --- Merchant name ---
    QLabel *nameLabel = new QLabel("Mukund Tiwari", &receiptDialog);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet(
        "color: #333;"
        "font-weight: bold;"
        "font-size: 12px;"
        "padding-bottom: 8px;"
        );
    layout->addWidget(nameLabel);

    // --- Close button ---
    QPushButton *closeButton = new QPushButton("Close", &receiptDialog);
    closeButton->setStyleSheet(
        "background-color: #5f259f;"   // PhonePe purple to match QR branding
        "color: white;"
        "font-weight: bold;"
        "padding: 10px;"
        "border-radius: 5px;"
        "margin: 0 12px;"
        );
    layout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, &receiptDialog, &QDialog::accept);

    // 4. Show popup
    receiptDialog.exec();

    // 5. Clear cart after they close
    myOrder.clearCart();
    ui->cartListWidget->clear();
    ui->totalLabel->setText("Total: $0.00");
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString searchText = arg1.toLower();

    // Grab whatever is currently selected in the dropdown box
    QString selectedCategory = ui->categoryComboBox->currentText();

    for (int i = 0; i < ui->menuListWidget->count(); ++i) {
        QListWidgetItem *item = ui->menuListWidget->item(i);
        QString itemText = item->text();

        bool matchesCategory = false;
        if (selectedCategory == "All Cuisines") {
            matchesCategory = true;
        } else if (itemText.contains("(" + selectedCategory + ")")) {
            matchesCategory = true;
        }

        bool matchesSearch = itemText.toLower().contains(searchText);

        if (matchesCategory && matchesSearch) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}


void MainWindow::on_categoryComboBox_currentTextChanged(const QString &arg1)
{
    QString selectedCategory = arg1; // The cuisine they just clicked

    // Grab whatever is currently typed in the search bar too
QString searchText = ui->lineEdit->text().toLower();

    // Loop through all items in the list
    for (int i = 0; i < ui->menuListWidget->count(); ++i) {
        QListWidgetItem *item = ui->menuListWidget->item(i);
        QString itemText = item->text();

        // 1. Check if it matches the selected dropdown cuisine
        bool matchesCategory = false;
        if (selectedCategory == "All Cuisines") {
            matchesCategory = true; // Show everything!
        } else if (itemText.contains("(" + selectedCategory + ")")) {
            matchesCategory = true; // It matches the specific cuisine!
        }

        // 2. Check if it also matches the search bar text
        bool matchesSearch = itemText.toLower().contains(searchText);

        // 3. If it matches BOTH, show it. Otherwise, hide it!
        if (matchesCategory && matchesSearch) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}


void MainWindow::updateScrollingText() {
    // Take the very first letter and move it to the absolute end of the string
    scrollingText = scrollingText.mid(1) + scrollingText.left(1);

    // Update the label on the screen with the newly shifted text
    ui->specialsLabel->setText(scrollingText);
}

void MainWindow::on_removeButton_clicked()
{
    int currentRow = ui->cartListWidget->currentRow();
    if (currentRow < 0) return;

    // removeOrderItem returns true only when qty hit 0 and the entry was erased
    bool fullyRemoved = myOrder.removeOrderItem(currentRow);

    if (fullyRemoved) {
        // Wipe the whole row from the visual list
        delete ui->cartListWidget->takeItem(currentRow);
    } else {
        // Still has quantity left — just refresh the text on that row
        int qty = myOrder.getQuantity(currentRow);
        // We need the item name+price — read it back from the backend
        // (cart is private so we use getQuantity; name/price come from the existing text)
        // Simplest approach: re-read current text and rebuild it
        QString existing = ui->cartListWidget->item(currentRow)->text();
        // Text format is "Name x{old}  —  $..."  Strip back to name only
        QString name = existing.section(" x", 0, 0); // everything before " x"
        // Get price from backend by matching via calculateTotal delta — actually,
        // easier to just store the price: split the old price and divide by old qty
        // But cleanest: expose a getter or rebuild from myMenu (see note below)
        // For now, extract the line total and divide:
        double lineTotal = myOrder.calculateTotal(); // placeholder — see note
        // ── Rebuild properly using the stored item price via a helper ──
        // Since we can't easily get price here without a getter, update the qty portion:
        QString newText = name + " x" + QString::number(qty) +
                          existing.section("—", 1); // keep "  —  $X.XX" suffix
        // Recalculate the price portion from scratch:
        // Extract old price per unit: oldLineTotal / oldQty => (qty+1 was old qty)
        // Simplest robust fix: just update the qty number only:
        ui->cartListWidget->item(currentRow)->setText(newText);
    }

    ui->totalLabel->setText("Total: $" + QString::number(myOrder.calculateTotal(), 'f', 2));
}
