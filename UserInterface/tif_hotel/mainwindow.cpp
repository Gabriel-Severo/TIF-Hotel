#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "styles.h"
#include "pessoa.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btn_login->setStyleSheet(Styles::PushButtonStyle);
    ui->btn_signin->setStyleSheet(Styles::PushButtonStyle);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_signin_clicked()
{
    ui_register = new Register();
    ui_register->setStyleSheet(Styles::ScreenStyle);
    ui_register->exec();
}

void MainWindow::on_btn_login_clicked()
{
    Pessoa *pessoa = new Pessoa;

    if(ui->txt_cpf->text().isEmpty() || ui->txt_senha->text().isEmpty())
    {
        QMessageBox::warning(this, "warning", "Campo de texto vazio");
        ui->txt_cpf->setFocus();
        return;
    }
    pessoa->setNome("João da Silva");
    pessoa->setEmail(pessoa->getNome()+"@email.com.br");
    pessoa->setCPF("123.456.789-12");

    ui->txt_cpf->clear();
    ui->txt_senha->clear();

    ui_menu = new Menu(nullptr, pessoa);
    ui_menu->setStyleSheet(Styles::ScreenStyle);
    ui_menu->exec();
}
