#include "Mainwindow.h"
#include <QInputDialog>


Mainwindow::Mainwindow()
{
    setWindowTitle("2048");

    /* add game window */
    game = new Game(this);
    setCentralWidget(game);

    /* create action */
    restartAct = new QAction("&Restart", this);
    QObject::connect(restartAct, SIGNAL(triggered()), game, SLOT(restart()));
    giveupAct = new QAction("&GiveUp", this);
    QObject::connect(giveupAct, SIGNAL(triggered()), game, SLOT(toIndexScene()));

    /* create menu */
    menu = menuBar()->addMenu("&Option");
    menu->addAction(restartAct);
    menu->addAction(giveupAct);
    menu->setDisabled(true);
    QObject::connect(game, SIGNAL(toGame()), this, SLOT(menuEnable()));
    QObject::connect(game, SIGNAL(toIndex()), this, SLOT(menuDisable()));

    setFixedSize(sizeHint());   // disable to resize from drag border
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

void Mainwindow::menuEnable()
{
    menu->setEnabled(true);
}

void Mainwindow::menuDisable()
{
    menu->setDisabled(true);
}

