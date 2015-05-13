#include "Game.h"
#define dbName "rank.db"
#define tbName "rank"

Game::Game()
{
    gameScene = new GameScene(this);
    setScene(gameScene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(500,650);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if(!db.open())
    {
        qDebug() << "DataBase " << dbName <<" can't be opened";
        exit(EXIT_FAILURE);
    }
    else
    {
        QSqlQuery qry;
        qry.exec(QString("CREATE TABLE %1 (id INT PRIMARY KEY, name TEXT, score INT)").arg(tbName));
    }

}

void Game::init()
{
    gameScene->init();  // propagate
}

void Game::setUserName(QString name)
{
    userName = name;
}

QString Game::getuserName()
{
    return userName;
}


