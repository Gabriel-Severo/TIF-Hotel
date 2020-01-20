#ifndef STYLES_H
#define STYLES_H

#include <QString>

extern QString PushButtonStyle;
extern QString ScreenStyle;

class Pessoa
{
public:
    QString nome;
    QString email;

    void setNome(QString nome);
    QString getNome();
    void setEmail(QString email);
    QString getEmail();
};




#endif // STYLES_H
