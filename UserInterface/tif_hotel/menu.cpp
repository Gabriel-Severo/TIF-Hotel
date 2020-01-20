#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"

Menu::Menu(QWidget *parent, Pessoa* p) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->btn_reserva->setStyleSheet(PushButtonStyle);
    ui->btn_consulta->setStyleSheet(PushButtonStyle);

    ui->txt_nome->setText(p->getNome());
    ui->txt_email->setText(p->getEmail());
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    Menu::close();
}
