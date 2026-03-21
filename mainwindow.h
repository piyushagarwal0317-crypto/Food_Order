#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Menu.h"    // Bringing in your backend!
#include "Order.h"   // Bringing in your backend!
#include <QTimer>   // 1. ADD THIS AT THE TOP

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addToCartButton_clicked();

    void on_checkoutButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_categoryComboBox_currentTextChanged(const QString &arg1);

    void updateScrollingText();

    void on_removeButton_clicked();

private:
    Ui::MainWindow *ui;

    // Here are your C++ engine objects!
    Menu myMenu;
    Order myOrder;

    // ADD THESE TWO LINES FOR THE SCROLLING TEXT:
    QTimer *scrollTimer;
    QString scrollingText;
};
#endif // MAINWINDOW_H