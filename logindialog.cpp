#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QRegularExpression>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->usernameEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    // 1. Grab the text from your input boxes
    QString username = ui->usernameEdit->text();
    QString emailPhone = ui->emailPhoneEdit->text();
    QString password = ui->passwordEdit->text();

    // 2. Check if the user left anything completely blank
    if(username.isEmpty() || emailPhone.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all the fields before logging in!");
        return;
    }

    // 3. The Password Rule Checker (Regex)
    // Needs: 1 lowercase, 1 uppercase, 1 digit, 1 symbol, and at least 8 chars total
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    QRegularExpressionMatch match = regex.match(password);

    // 4. Test the password against the rules
    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Weak Password",
                             "Password must be at least 8 characters long and contain:\n"
                             "- One uppercase letter\n"
                             "- One lowercase letter\n"
                             "- One number\n"
                             "- One symbol (@$!%*?&)");
        return; // Stops the login process here
    }

    // 5. If everything is perfect, accept the login and close this dialog!
    accept();
}

