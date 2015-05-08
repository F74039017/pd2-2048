#include "Mainwindow.h"
#include <QInputDialog>


Mainwindow::Mainwindow()
{
    /* add menu */
    menu = new QMenu();
    menu = menuBar()->addMenu("&Option");

    /* add game window */
    game = new Game();
    setCentralWidget(game);
}

void Mainwindow::startGame()
{
    game->init();   // start game
}

void Mainwindow::askUserName()
{
    bool ok;
    QString text = QInputDialog::getText(this, "Your name?", "User name:", QLineEdit::Normal, "Anonymous", &ok);
    if(!ok)
        game->setUserName("Anonymous");
    else
        game->setUserName(text);
}


