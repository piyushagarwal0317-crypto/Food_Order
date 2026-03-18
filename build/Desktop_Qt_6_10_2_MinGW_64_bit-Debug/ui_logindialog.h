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
        passwordEdit = new QLineEdit(LoginDialog);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setGeometry(QRect(120, 230, 181, 29));
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);
        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(120, 300, 111, 31));
        usernameEdit = new QLineEdit(LoginDialog);
        usernameEdit->setObjectName("usernameEdit");
        usernameEdit->setGeometry(QRect(120, 110, 181, 29));
        label_4 = new QLabel(LoginDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(90, 20, 211, 71));
        QFont font;
        font.setBold(true);
        label_4->setFont(font);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Username :", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Email/Phone :", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "Password :", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        label_4->setText(QCoreApplication::translate("LoginDialog", "Welcome to Food Villa", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
