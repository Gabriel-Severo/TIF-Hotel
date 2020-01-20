#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "styles.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btn_login->setStyleSheet(PushButtonStyle);
    ui->btn_signin->setStyleSheet(PushButtonStyle);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_signin_clicked()
{
    ui_register = new Register();
    ui_register->setStyleSheet(ScreenStyle);
    ui_register->exec();
}

void MainWindow::on_btn_login_clicked()
{
    Pessoa *pessoa = new Pessoa();

    if(ui->txt_nome->text().isEmpty() || ui->txt_senha->text().isEmpty())
    {
        QMessageBox::warning(this, "warning", "Campo de texto vazio");
        ui->txt_nome->setFocus();
        return;
    }
    pessoa->setNome(ui->txt_nome->text());
    pessoa->setEmail(pessoa->getNome()+"@email.com.br");

    ui->txt_nome->clear();
    ui->txt_senha->clear();

    ui_menu = new Menu(nullptr, pessoa);
    ui_menu->setStyleSheet(ScreenStyle);
    ui_menu->exec();
}
