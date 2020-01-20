#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <register.h>
#include <menu.h>

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

    void on_btn_signin_clicked();

    void on_btn_login_clicked();

private:
    Ui::MainWindow *ui;
    Register *ui_register;
    Menu *ui_menu;
};
#endif // MAINWINDOW_H
