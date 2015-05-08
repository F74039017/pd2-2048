#include <QApplication>
#include <QtWidgets>
#include <QtSql>
#include "Mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwindow w;
    w.show();
    w.askUserName();
    w.startGame();

    return a.exec();
}
