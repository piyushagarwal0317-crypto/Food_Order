/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *emailPhoneEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QLineEdit *usernameEdit;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *backgroundLabel;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(403, 368);
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 170, 78, 21));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 110, 95, 21));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 230, 73, 21));
        emailPhoneEdit = new QLineEdit(LoginDialog);
        emailPhoneEdit->setObjectName("emailPhoneEdit");
        emailPhoneEdit->setGeometry(QRect(120, 170, 181, 29));
        emailPhoneEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #1c2833;  /* Deep Midnight Blue */\n"
"    color: #fdf2e9;             /* Soft off-white text so it isn't harsh */\n"
"    border: 2px solid #2980b9;  /* Bright blue border */\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #f39c12;  /* Border turns warm orange when typing */\n"
"}"));
        passwordEdit = new QLineEdit(LoginDialog);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(120, 230, 181, 29));
        passwordEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #1c2833;  /* Deep Midnight Blue */\n"
"    color: #fdf2e9;             /* Soft off-white text so it isn't harsh */\n"
"    border: 2px solid #2980b9;  /* Bright blue border */\n"
"    border-radius: 8px;\n"
"    padding: 5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #f39c12;  /* Border turns warm orange when typing */\n"
"}"));
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);
        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(110, 290, 111, 41));
        loginButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #E0E0E0; /* A nice, light faded gray */\n"
"    color: #333333; /* Dark gray text so it's easy to read */\n"
"    font-weight: bold;\n"
"    border-radius: 8px;\n"
"    padding: 8px;\n"
"    border: 1px solid #BDBDBD; /* Adds a very subtle outline */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #D6D6D6; /* Gets slightly darker when the mouse is over it */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #BDBDBD; /* Gets even darker when you actually click it */\n"
"}"));
        usernameEdit = new QLineEdit(LoginDialog);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setGeometry(QRect(120, 110, 181, 31));
        usernameEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #1c2833;  /* Deep Midnight Blue */\n"
"    color: #fdf2e9;             /* Soft off-white text so it isn't harsh */\n"
"    border: 2px solid #2980b9;  /* Bright blue border */\n"
"    border-radius: 8px;QLineEdit {\n"
"    background-color: #1c2833;  /* Your midnight navy color */\n"
"    color: #fdf2e9;\n"
"    border: 2px solid #2980b9;\n"
"    border-radius: 8px;\n"
"    \n"
"    /* FIX: Reduce left and right padding to 2px to stop cutting off text */\n"
"    padding-left: 2px;\n"
"    padding-right: 2px;\n"
"    padding-top: 5px;\n"
"    padding-bottom: 5px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #f39c12;\n"
"}\n"
"    padding: 5px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 2px solid #f39c12;  /* Border turns warm orange when typing */\n"
"}"));
        label_4 = new QLabel(LoginDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(70, 20, 211, 71));
        QFont font;
        font.setBold(true);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_5 = new QLabel(LoginDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 10, 63, 61));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/biryani.png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(LoginDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(280, 20, 63, 51));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/hamburger.png")));
        label_6->setScaledContents(true);
        backgroundLabel = new QLabel(LoginDialog);
        backgroundLabel->setObjectName("backgroundLabel");
        backgroundLabel->setGeometry(QRect(-10, -10, 471, 381));
        backgroundLabel->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        emailPhoneEdit->raise();
        passwordEdit->raise();
        loginButton->raise();
        usernameEdit->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Username :", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Email/Phone :", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "Password :", nullptr));
        emailPhoneEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "e.g.  foodie123", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        usernameEdit->setPlaceholderText(QCoreApplication::translate("LoginDialog", "xyz@gmail.com", nullptr));
        label_4->setText(QCoreApplication::translate("LoginDialog", "Welcome to Food Villa", nullptr));
        label_5->setText(QString());
        label_6->setText(QString());
        backgroundLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
