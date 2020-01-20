#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"

Menu::Menu(QWidget *parent, Pessoa* p) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->btn_reserva->setStyleSheet(Styles::optionButtonStyle);
    ui->btn_consulta->setStyleSheet(Styles::optionButtonStyle);
    ui->pushButton->setStyleSheet(Styles::PushButtonStyle);

    ui->txt_nome->setText(p->getNome());
    ui->txt_email->setText(p->getEmail());
    ui->txt_cpf->setText(p->getCPF());
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    Menu::close();
}
