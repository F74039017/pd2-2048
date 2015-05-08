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
    QAction *restart;
    QAction *showrank;
    Game *game;
};


#endif // MAINWINDOW

