#include "register.h"
#include "ui_register.h"
#include "styles.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    ui->btn_cadastrar->setStyleSheet(PushButtonStyle);
}

Register::~Register()
{
    delete ui;
}

void Register::on_btn_cadastrar_clicked()
{
    close();
}
