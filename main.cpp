#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QQuickView>
#include <QUrl>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Show the QML splash animation first
    QQuickView *qmlView = new QQuickView;
    qmlView->setSource(QUrl("qrc:/animation.qml"));
    qmlView->setFlags(Qt::FramelessWindowHint);
    qmlView->show();

    // After 3 seconds, close splash and show login
    QTimer::singleShot(3000, [qmlView]() {
        qmlView->close();
        qmlView->deleteLater();

        LoginDialog *login = new LoginDialog();
        if (login->exec() == QDialog::Accepted) {
            // Login succeeded — MainWindow is already shown inside the dialog
            // Nothing to do here, the app event loop keeps running
        } else {
            // User closed/cancelled the login dialog
            qApp->quit();
        }
        login->deleteLater();
    });

    return a.exec();
}