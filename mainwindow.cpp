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
    // 1. Check if the user actually selected an item in the menu list
    int currentRow = ui->menuListWidget->currentRow();
    if (currentRow < 0) {
        return; // They didn't select anything, so do nothing!
    }

    // 2. Get the exact item they clicked from your C++ backend
    std::vector<MenuItem> items = myMenu.getItems();
    MenuItem selectedFood = items[currentRow];

    // 3. Add it to your C++ Order engine (assuming quantity 1 for simplicity)
    myOrder.addItemToCart(selectedFood, 1);

    // 4. Update the visual Cart List on the screen
    QString cartText = QString::fromStdString(selectedFood.getName()) + " - $" + QString::number(selectedFood.getPrice());
    ui->cartListWidget->addItem(cartText);

    // 5. Update the visual Total Label
    double currentTotal = myOrder.calculateTotal();
    ui->totalLabel->setText("Total: $" + QString::number(currentTotal, 'f', 2));
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
        // 1. Find out exactly which row the user highlighted in the visual list
        int currentRow = ui->cartListWidget->currentRow();

        // 2. Failsafe: If they click the button WITHOUT selecting an item, currentRow is -1.
        // We only want to run the deletion code if they actually selected something (>= 0).
        if (currentRow >= 0) {

            // 3. Delete it from your C++ backend vector
            myOrder.removeOrderItem(currentRow);

            // 4. Delete it from the visual Qt list on the screen
            delete ui->cartListWidget->takeItem(currentRow);

            // 5. Recalculate the math and update the visual Total Label!
            // (Using QString::number to force exactly 2 decimal places)
            ui->totalLabel->setText("Total: $" + QString::number(myOrder.calculateTotal(), 'f', 2));
        }

    }

