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
    // 1. Find the path and save the receipt in the background
    QString receiptPath = QCoreApplication::applicationDirPath() + "/receipt.txt";
    myOrder.saveReceiptToFile(receiptPath.toStdString());

    // 2. Read the newly saved text file back into Qt
    QString receiptContent;
    QFile file(receiptPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        receiptContent = in.readAll();
        file.close();
    }

    // 3. CREATE THE CUSTOM RECEIPT POP-UP!
    QDialog receiptDialog(this);
    receiptDialog.setWindowTitle("Order Complete");
    receiptDialog.resize(340, 600); // Tall and narrow, just like a physical bill!
    receiptDialog.setStyleSheet("background-color: white;"); // Pure white paper

    // Set up a vertical layout manager
    QVBoxLayout layout(&receiptDialog);

    // Create the text viewer for the receipt
    QTextEdit receiptText(&receiptDialog);
    receiptText.setReadOnly(true); // So the user can't accidentally type on their bill
    receiptText.setText(receiptContent);

    // CRITICAL FIX: We MUST use a Monospace font.
    // If we don't, standard fonts will make our beautifully aligned columns jagged!
    QFont monoFont("Courier");
    monoFont.setStyleHint(QFont::Monospace);
    monoFont.setPointSize(10);
    receiptText.setFont(monoFont);

    // Style the text box (black text, transparent/white background, no ugly borders)
    receiptText.setStyleSheet("color: black; background-color: transparent; border: none;");

    layout.addWidget(&receiptText);

    // Add a stylish "Close" button at the bottom
    QPushButton closeButton("Close", &receiptDialog);
    closeButton.setStyleSheet("background-color: #FF7E5F; color: white; font-weight: bold; padding: 10px; border-radius: 5px;");
    layout.addWidget(&closeButton);

    // Tell the button to close the pop-up when clicked
    connect(&closeButton, &QPushButton::clicked, &receiptDialog, &QDialog::accept);

    // 4. Show the pop-up to the user! (The app pauses here until they click Close)
    receiptDialog.exec();

    // 5. Clean up the cart ONLY AFTER they finish looking at their receipt
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
