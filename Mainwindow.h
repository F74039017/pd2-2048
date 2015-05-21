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
    QMenu *optionMenu;
    QMenu *modeMenu;
    QAction *restartAct;
    QAction *giveupAct;
    QAction *survivalAct;
    QAction *classicAct;
    Game *game;
};


#endif // MAINWINDOW

