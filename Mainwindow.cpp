#include "Mainwindow.h"


Mainwindow::Mainwindow()
{
    /* add menu */
    menu = new QMenu();
    menu = menuBar()->addMenu("&Option");

    /* add game window */
    game = new Game();
    setCentralWidget(game);
    game->start();
}
