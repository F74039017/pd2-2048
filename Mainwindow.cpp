#include "Mainwindow.h"
#include <QInputDialog>

bool Mainwindow::soundMute = false;  //-- true for test
bool Mainwindow::musicMute = false;

Mainwindow::Mainwindow()
{
    setWindowTitle("2048");

    /* add game window */
    game = new Game(this);
    setCentralWidget(game);

    /* create action */
        /* Mode */
    classicAct = new QAction("&Classic", this);
    QObject::connect(classicAct, SIGNAL(triggered()), game, SLOT(setClassMode()));
    survivalAct = new QAction("&Survival", this);
    QObject::connect(survivalAct, SIGNAL(triggered()), game, SLOT(setSurvivalMode()));
    xtileAct = new QAction("&Xtile", this);
    QObject::connect(xtileAct, SIGNAL(triggered()), game, SLOT(setXtileMode()));
        /* Option */
    restartAct = new QAction("&Restart", this);
    QObject::connect(restartAct, SIGNAL(triggered()), game, SLOT(restart()));
    giveupAct = new QAction("&GiveUp", this);
    QObject::connect(giveupAct, SIGNAL(triggered()), game, SLOT(toIndexScene()));
        /* Mute */
    musicMuteAct = new QAction("&Music", this);
    QObject::connect(musicMuteAct, SIGNAL(triggered()), game, SLOT(muteMusic()));
    soundMuteAct = new QAction("&Sound", this);
    QObject::connect(soundMuteAct, SIGNAL(triggered()), this, SLOT(muteSound()));


    /* create menu */
        /* Mode */
    modeMenu = menuBar()->addMenu("&Mode");
    modeMenu->addAction(classicAct);
    modeMenu->addAction(xtileAct);
    modeMenu->addAction(survivalAct);
        /* Option */
    optionMenu = menuBar()->addMenu("&Option");
    optionMenu->addAction(restartAct);
    optionMenu->addAction(giveupAct);
    optionMenu->setDisabled(true);
    QObject::connect(game, SIGNAL(toGame()), this, SLOT(menuEnable()));
    QObject::connect(game, SIGNAL(toIndex()), this, SLOT(menuDisable()));
        /* Mute */
    muteMenu = menuBar()->addMenu("&Mute");
    muteMenu->addAction(musicMuteAct);
    muteMenu->addAction(soundMuteAct);

    setFixedSize(sizeHint());   // disable to resize from drag border
}

void Mainwindow::startGame()
{
    game->init();   // start game
}

void Mainwindow::askUserName()  // input dialog
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
    optionMenu->setEnabled(true);
}

void Mainwindow::menuDisable()
{
    optionMenu->setDisabled(true);
}

void Mainwindow::muteSound()
{
    soundMute = !soundMute;
}

