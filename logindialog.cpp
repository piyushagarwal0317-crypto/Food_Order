#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QMovie>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include "mainwindow.h"

// ─── CSV Column Layout ───────────────────────────────────────────
// email , username , password , registered_date
// ────────────────────────────────────────────────────────────────
static const QString CSV_FILE = "users.csv";
static const QString CSV_HEADER = "email,username,password,registered_date";

// Helper: reads CSV and returns all rows as list-of-lists (skips header)
static QList<QStringList> readCSV()
{
    QList<QStringList> rows;
    QFile file(CSV_FILE);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return rows;

    QTextStream in(&file);
    bool firstLine = true;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (firstLine) { firstLine = false; continue; } // skip header
        if (line.isEmpty()) continue;
        rows.append(line.split(','));
    }
    file.close();
    return rows;
}

// Helper: ensure the CSV file exists with a header row
static void ensureCSVExists()
{
    QFile file(CSV_FILE);
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << CSV_HEADER << "\n";
            file.close();
        }
    }
}

// ─────────────────────────────────────────────────────────────────

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // Background animation
    QMovie *movie = new QMovie(":/bg.gif");
    ui->backgroundLabel->setMovie(movie);
    movie->start();

    ensureCSVExists(); // Make sure users.csv is ready

    // NOTE: In your .ui file the widget names are swapped:
    //   usernameEdit   → holds EMAIL   (label says "Email/Phone")
    //   emailPhoneEdit → holds USERNAME (label says "Username")
    // We use them as-is to stay compatible with your .ui file.
    ui->usernameEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// ─── LOGIN ───────────────────────────────────────────────────────
void LoginDialog::on_loginButton_clicked()
{
    QString typedEmail = ui->usernameEdit->text().trimmed();

    if (typedEmail.isEmpty()) {
        QMessageBox::warning(this, "Missing Info", "Please enter your email to log in.");
        return;
    }

    QList<QStringList> rows = readCSV();
    bool found = false;
    for (const QStringList &row : rows) {
        if (row.size() >= 1 && row[0].trimmed() == typedEmail) {
            found = true;
            break;
        }
    }

    if (found) {
        MainWindow *mainWindow = new MainWindow();
        mainWindow->setAttribute(Qt::WA_DeleteOnClose); // auto-cleanup on close
        mainWindow->show();
        accept(); // ← This closes the dialog cleanly and returns Accepted to main.cpp
    } else {
        QMessageBox::critical(this, "Access Denied",
                              "Email not found.\nPlease register first or check your spelling.");
    }
}

// ─── REGISTER ────────────────────────────────────────────────────
void LoginDialog::on_registerButton_clicked()
{
    // Collect all three fields
    QString email    = ui->usernameEdit->text().trimmed();    // Email field
    QString username = ui->emailPhoneEdit->text().trimmed();  // Username field
    QString password = ui->passwordEdit->text();              // Password field

    // ── Validation ──────────────────────────────────────────────
    if (email.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Incomplete Form",
                             "Please fill in Email, Username, and Password before registering.");
        return;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "Weak Password",
                             "Password must be at least 6 characters long.");
        return;
    }

    // Reject commas — they would break the CSV format
    if (email.contains(',') || username.contains(',') || password.contains(',')) {
        QMessageBox::warning(this, "Invalid Characters",
                             "Fields cannot contain commas ( , ).");
        return;
    }

    // ── Duplicate Check ─────────────────────────────────────────
    QList<QStringList> rows = readCSV();
    for (const QStringList &row : rows) {
        if (row.size() >= 1 && row[0].trimmed() == email) {
            QMessageBox::information(this, "Already Registered",
                                     "This email is already registered.\nJust log in with your email!");
            return;
        }
    }

    // ── Write to CSV ─────────────────────────────────────────────
    QFile file(CSV_FILE);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << email << ","
            << username << ","
            << password << ","
            << QDate::currentDate().toString("yyyy-MM-dd") << "\n";
        file.close();

        QMessageBox::information(this, "Registered!",
                                 QString("Welcome, %1!\nYou can now log in with just your email.").arg(username));

        // Clear the form for a clean login experience
        ui->usernameEdit->clear();
        ui->emailPhoneEdit->clear();
        ui->passwordEdit->clear();
        ui->usernameEdit->setFocus();
    } else {
        QMessageBox::critical(this, "File Error",
                              "Could not save your details. Check app write permissions.");
    }
}