#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QQuickView> // Needed for the QML animation
#include <QUrl>
#include <QTimer>     // Needed for the delay timer

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. SETUP AND SHOW THE QML ANIMATION FIRST
    QQuickView *qmlView = new QQuickView;
    qmlView->setSource(QUrl("qrc:/animation.qml")); // Using the crash-proof resource path!
    qmlView->setFlags(Qt::FramelessWindowHint);     // Removes the ugly window borders
    qmlView->show();

    // 2. PREPARE THE MAIN WINDOW (Hidden for now)
    // We use 'new' here so it stays alive in the background while the timer runs
    MainWindow *w = new MainWindow();

    // 3. THE TIMER (3000 milliseconds = 3 seconds)
    QTimer::singleShot(3000, [qmlView, w]() {

        // Time is up! Close the animation
        qmlView->close();
        qmlView->deleteLater();

        // Now, pop open the Login window
        LoginDialog login;
        if (login.exec() == QDialog::Accepted) {

            // They logged in successfully! Show the main restaurant menu.
            w->show();

        } else {
            // They clicked cancel or closed the box. Quit the app entirely.
            qApp->quit();
        }
    });

    // Start the main Qt engine!
    return a.exec();
}