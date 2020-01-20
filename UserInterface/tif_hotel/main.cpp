#include "mainwindow.h"

#include <QApplication>
#include <styles.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet(Styles::ScreenStyle);
    w.show();
    return a.exec();
}
