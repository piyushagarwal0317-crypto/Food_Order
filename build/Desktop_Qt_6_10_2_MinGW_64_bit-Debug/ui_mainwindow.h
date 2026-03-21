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
        MainWindow->setStyleSheet(QString::fromUtf8("/* 1. Make the main background pure white */\n"
"QWidget#centralwidget {\n"
"    background-color: #FFFFFF;\n"
"}\n"
"\n"
"/* 2. Style the Menu and Cart lists */\n"
"QListWidget {\n"
"    background-color: #F8F9FA;\n"
"    border: 1px solid #E0E0E0;\n"
"    border-radius: 8px;\n"
"    color: #1A1A1D;\n"
"    font-size: 14px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #FEB47B;\n"
"    color: white;\n"
"}\n"
"\n"
"/* 3. Style the Buttons */\n"
"QPushButton {\n"
"    background-color: #FF7E5F;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 8px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #E23E57;\n"
"}\n"
"\n"
"/* 4. Style the text labels */\n"
"QLabel {\n"
"    color: #1A1A1D;\n"
"    font-weight: bold;\n"
"    font-size: 16px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(40, 60, 113, 26));
        categoryComboBox = new QComboBox(centralwidget);
        categoryComboBox->setObjectName("categoryComboBox");
        categoryComboBox->setGeometry(QRect(180, 60, 151, 26));
        specialsLabel = new QLabel(centralwidget);
        specialsLabel->setObjectName("specialsLabel");
        specialsLabel->setGeometry(QRect(60, 20, 661, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Monospac821 BT")});
        font.setBold(true);
        specialsLabel->setFont(font);
        specialsLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        addToCartButton = new QPushButton(centralwidget);
        addToCartButton->setObjectName("addToCartButton");
        addToCartButton->setGeometry(QRect(40, 480, 256, 29));
        QFont font1;
        font1.setBold(true);
        addToCartButton->setFont(font1);
        totalLabel = new QLabel(centralwidget);
        totalLabel->setObjectName("totalLabel");
        totalLabel->setGeometry(QRect(540, 100, 161, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe Fluent Icons")});
        font2.setBold(true);
        totalLabel->setFont(font2);
        checkoutButton = new QPushButton(centralwidget);
        checkoutButton->setObjectName("checkoutButton");
        checkoutButton->setGeometry(QRect(480, 480, 131, 31));
        checkoutButton->setFont(font1);
        cartListWidget = new QListWidget(centralwidget);
        cartListWidget->setObjectName("cartListWidget");
        cartListWidget->setGeometry(QRect(480, 140, 271, 331));
        menuListWidget = new QListWidget(centralwidget);
        menuListWidget->setObjectName("menuListWidget");
        menuListWidget->setGeometry(QRect(41, 138, 251, 331));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(110, 90, 111, 41));
        label->setFont(font1);
        removeButton = new QPushButton(centralwidget);
        removeButton->setObjectName("removeButton");
        removeButton->setGeometry(QRect(630, 480, 121, 31));
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
        specialsLabel->setText(QCoreApplication::translate("MainWindow", "                                   TextLabel", nullptr));
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
