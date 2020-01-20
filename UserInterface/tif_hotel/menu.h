#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "pessoa.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr, Pessoa* pessoa = nullptr);
    ~Menu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Menu *ui;
    //MainWindow *ui_mainwindow;
};

#endif // MENU_H
