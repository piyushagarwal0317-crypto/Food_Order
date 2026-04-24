/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QComboBox *categoryComboBox;
    QLabel *specialsLabel;
    QPushButton *addToCartButton;
    QLabel *totalLabel;
    QPushButton *checkoutButton;
    QListWidget *cartListWidget;
    QListWidget *menuListWidget;
    QLabel *label;
    QPushButton *removeButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("/* === MAIN BACKGROUND === */\n"
"QWidget#centralwidget {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #fff8f0, stop:0.5 #fdebd0, stop:1 #fad7a0);\n"
"}\n"
"\n"
"/* === MENU & CART LISTS === */\n"
"QListWidget {\n"
"    background-color: rgba(255, 255, 255, 0.75);\n"
"    border: 1.5px solid #f0a500;\n"
"    border-radius: 12px;\n"
"    color: #5a3200;\n"
"    font-size: 14px;\n"
"    padding: 6px;\n"
"}\n"
"QListWidget::item {\n"
"    padding: 6px 8px;\n"
"    border-radius: 6px;\n"
"}\n"
"QListWidget::item:hover {\n"
"    background-color: rgba(240, 165, 0, 0.12);\n"
"}\n"
"QListWidget::item:selected {\n"
"    background-color: rgba(240, 140, 0, 0.30);\n"
"    color: #7a3e00;\n"
"}\n"
"\n"
"/* === LABELS === */\n"
"QLabel {\n"
"    color: #7a3e00;\n"
"    font-weight: bold;\n"
"    font-size: 16px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* === SEARCH BAR === */\n"
"QLineEdit {\n"
"    background-color: rgba(255, 255, 255, 0.80);\n"
"    border: 1.5px solid #f0a500;\n"
""
                        "    border-radius: 15px;\n"
"    padding: 6px 15px;\n"
"    color: #5a3200;\n"
"    font-size: 14px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #e07b00;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* === DROPDOWN === */\n"
"QComboBox {\n"
"    background-color: rgba(255, 255, 255, 0.80);\n"
"    border: 1.5px solid #f0a500;\n"
"    border-radius: 8px;\n"
"    padding: 5px 10px;\n"
"    color: #7a3e00;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #fff8f0;\n"
"    color: #5a3200;\n"
"    selection-background-color: rgba(240, 165, 0, 0.25);\n"
"    border: 1px solid #f0a500;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"}\n"
"\n"
"/* === SPECIALS TICKER === */\n"
"QLabel#specialsLabel {\n"
"    background-color: #5a3200;\n"
"    color: #FFD97A;\n"
"    border: 2px solid #f0a500;\n"
"    border-radius: 12px;\n"
"    padding: 10px;\n"
"    font-weight: 900;\n"
"    font-size: 20px;\n"
"}\n"
"\n"
""
                        "/* === ADD TO CART BUTTON === */\n"
"QPushButton#addToCartButton {\n"
"    background-color: white;\n"
"    color: #28a745;\n"
"    border: 2px solid #28a745;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton#addToCartButton:hover {\n"
"    background-color: #28a745;\n"
"    color: white;\n"
"}\n"
"QPushButton#addToCartButton:pressed {\n"
"    background-color: #1e7e34;\n"
"    color: white;\n"
"}\n"
"\n"
"/* === CHECKOUT BUTTON === */\n"
"QPushButton#checkoutButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #f0a500, stop:1 #e07b00);\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton#checkoutButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #ffb700, stop:1 #f08c00);\n"
"}\n"
"QPushButton#checkoutButton:pressed {\n"
"    background: "
                        "qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #c87d00, stop:1 #a05e00);\n"
"}\n"
"\n"
"/* === REMOVE BUTTON === */\n"
"QPushButton#removeButton {\n"
"    background-color: #e74c3c;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton#removeButton:hover {\n"
"    background-color: #c0392b;\n"
"}\n"
"\n"
"/* === MENU BAR === */\n"
"QMenuBar {\n"
"    background-color: #fdebd0;\n"
"    color: #7a3e00;\n"
"}\n"
"QStatusBar {\n"
"    background-color: #fdebd0;\n"
"    color: #b07820;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(20, 100, 161, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("/* --- SEARCH BAR STYLING --- */\n"
"\n"
"/* 1. The Search Text Box */\n"
"QLineEdit {\n"
"    background-color: #F8F9FA;\n"
"    border: 2px solid #E0E0E0;\n"
"    border-radius: 15px; /* Gives it a nice round pill shape! */\n"
"    padding: 6px 15px;\n"
"    color: #1A1A1D;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Make the border glow Coral when the user clicks to type! */\n"
"QLineEdit:focus {\n"
"    border: 2px solid #FF7E5F; \n"
"}\n"
"\n"
"/* 2. The Search Button */\n"
"/* (Covering both QPushButton and QToolButton just in case!) */\n"
"QPushButton#searchButton, QToolButton {\n"
"    background-color: #1A1A1D; /* A sleek dark gray to contrast with your Coral buttons */\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 15px; /* Match the roundness of the search box */\n"
"    padding: 6px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton#searchButton:hover, QToolButton:hover {\n"
"    background-color: #4A4A4D; /* Lighter gray when hovered */\n"
"}"));
        categoryComboBox = new QComboBox(centralwidget);
        categoryComboBox->setObjectName("categoryComboBox");
        categoryComboBox->setGeometry(QRect(190, 100, 131, 31));
        categoryComboBox->setStyleSheet(QString::fromUtf8("/* Style the Drop-Down Menu so it isn't invisible! */\n"
"QComboBox {\n"
"    background-color: #F8F9FA;\n"
"    border: 1px solid #E0E0E0;\n"
"    border-radius: 6px;\n"
"    padding: 5px 10px;\n"
"    color: #1A1A1D;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"}"));
        specialsLabel = new QLabel(centralwidget);
        specialsLabel->setObjectName("specialsLabel");
        specialsLabel->setGeometry(QRect(240, 10, 291, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("Monospac821 BT")});
        font.setWeight(QFont::Black);
        specialsLabel->setFont(font);
        specialsLabel->setStyleSheet(QString::fromUtf8("/* --- SLIDING WINDOW / MARQUEE DISPLAY --- */\n"
"/* (Change 'scrollingLabel' to whatever your label's exact objectName is!) */\n"
"QLabel#specialsLabel {\n"
"    background-color: #1A1A1D;       /* A sleek, very dark gray/black background */\n"
"    color: #FF7E5F;                  /* Your signature Coral color for the text */\n"
"    border: 3px solid #E0E0E0;       /* A thick, modern border to frame it */\n"
"    border-radius: 12px;             /* Nice, heavily rounded corners */\n"
"    padding: 10px;                   /* Breathing room inside the box */\n"
"    font-weight: 900;                /* Extra bold text */\n"
"    font-size: 24px;                 /* Much larger text! */\n"
"}"));
        specialsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        addToCartButton = new QPushButton(centralwidget);
        addToCartButton->setObjectName("addToCartButton");
        addToCartButton->setGeometry(QRect(70, 480, 211, 41));
        QFont font1;
        font1.setBold(true);
        addToCartButton->setFont(font1);
        addToCartButton->setStyleSheet(QString::fromUtf8("/* --- ADD TO CART BUTTON --- */\n"
"/* Using the exact object name so it ONLY affects this specific button */\n"
"QPushButton#addToCartButton {\n"
"    background-color: #FFFFFF;       /* Pure white background */\n"
"    color: #28A745;                  /* Crisp, modern green text */\n"
"    border: 2px solid #28A745;       /* Matching green border */\n"
"    border-radius: 6px;              /* Keeps the modern rounded corners */\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Make it invert beautifully when the user hovers their mouse over it! */\n"
"QPushButton#addToCartButton:hover {\n"
"    background-color: #28A745;       /* Fills in green */\n"
"    color: #FFFFFF;                  /* Text turns white */\n"
"}"));
        totalLabel = new QLabel(centralwidget);
        totalLabel->setObjectName("totalLabel");
        totalLabel->setGeometry(QRect(550, 90, 161, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe Fluent Icons")});
        font2.setBold(true);
        totalLabel->setFont(font2);
        checkoutButton = new QPushButton(centralwidget);
        checkoutButton->setObjectName("checkoutButton");
        checkoutButton->setGeometry(QRect(480, 480, 131, 41));
        checkoutButton->setFont(font1);
        checkoutButton->setStyleSheet(QString::fromUtf8("/* --- CHECKOUT BUTTON --- */\n"
"QPushButton#checkoutButton {\n"
"    background-color: #28A745;       /* Solid green background */\n"
"    color: #FFFFFF;                  /* Pure white text */\n"
"    border: none;                    /* No border needed for a solid button */\n"
"    border-radius: 6px;              /* Smooth corners */\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* Make it darken slightly when the user hovers over it */\n"
"QPushButton#checkoutButton:hover {\n"
"    background-color: #218838;       /* A slightly deeper, richer green */\n"
"}"));
        cartListWidget = new QListWidget(centralwidget);
        cartListWidget->setObjectName("cartListWidget");
        cartListWidget->setGeometry(QRect(480, 140, 271, 331));
        menuListWidget = new QListWidget(centralwidget);
        menuListWidget->setObjectName("menuListWidget");
        menuListWidget->setGeometry(QRect(41, 138, 281, 331));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 40, 61, 41));
        label->setFont(font1);
        removeButton = new QPushButton(centralwidget);
        removeButton->setObjectName("removeButton");
        removeButton->setGeometry(QRect(630, 480, 121, 41));
        removeButton->setStyleSheet(QString::fromUtf8("background-color: #E23E57; color: white; border-radius: 5px; padding: 5px;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search Menu", nullptr));
        specialsLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        addToCartButton->setText(QCoreApplication::translate("MainWindow", "Add to Cart", nullptr));
        totalLabel->setText(QCoreApplication::translate("MainWindow", "Your Cart", nullptr));
        checkoutButton->setText(QCoreApplication::translate("MainWindow", "Checkout", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        removeButton->setText(QCoreApplication::translate("MainWindow", "Remove_Item", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
