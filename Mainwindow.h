#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QMenuBar>
#include "Game.h"

class Mainwindow: public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow();
    void startGame();
    void askUserName();

public slots:
    void menuEnable();
    void menuDisable();

private:
    QMenu *menu;
    QAction *restartAct;
    QAction *giveupAct;
    Game *game;
};


#endif // MAINWINDOW

