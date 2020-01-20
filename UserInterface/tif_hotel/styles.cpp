#include "styles.h"

QString PushButtonStyle = "QPushButton{background-color: black; color: white;}\
                           QPushButton::pressed{background-color: white; color: black;}";
QString ScreenStyle = "background-color: white;";

void Pessoa::setNome(QString nome)
{
    this->nome = nome;
}

QString Pessoa::getNome()
{
    return nome;
}

void Pessoa::setEmail(QString email)
{
    this->email = email;
}

QString Pessoa::getEmail()
{
    return email;
}

