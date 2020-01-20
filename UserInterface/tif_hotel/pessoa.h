#ifndef PESSOA_H
#define PESSOA_H

#include <QString>

class Pessoa
{
private:
    QString nome, email, cpf;

public:
    void setNome(QString nome);
    QString getNome();
    void setCPF(QString cpf);
    QString getCPF();
    void setEmail(QString email);
    QString getEmail();
};

#endif // PESSOA_H
