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

private:
    QMenu *menu;
    QAction *restartAct;
    QAction *showrankAct;
    Game *game;
};


#endif // MAINWINDOW

