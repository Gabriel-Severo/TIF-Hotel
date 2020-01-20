#include "pessoa.h"

void Pessoa::setNome(QString nome)
{
    this->nome = nome;
}

QString Pessoa::getNome()
{
    return nome;
}

void Pessoa::setCPF(QString cpf)
{
    this->cpf = cpf;
}

QString Pessoa::getCPF()
{
    return cpf;
}

void Pessoa::setEmail(QString email)
{
    this->email = email;
}

QString Pessoa::getEmail()
{
    return email;
}
