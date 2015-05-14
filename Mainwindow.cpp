#include "Mainwindow.h"
#include <QInputDialog>


Mainwindow::Mainwindow()
{
    setWindowTitle("2048");

    /* add game window */
    game = new Game();
    setCentralWidget(game);

    /* create action */
    restartAct = new QAction("&Restart", this);
    QObject::connect(restartAct, SIGNAL(triggered()), game, SLOT(restart()));

    /* create menu */
    menu = menuBar()->addMenu("&Option");
    menu->addAction(restartAct);
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

