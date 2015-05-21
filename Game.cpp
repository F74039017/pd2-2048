#include "Game.h"
#define dbName "rank.db"
#define tbName "rank"
#include "Mainwindow.h"

Game::Game(QWidget * parent)
    :QGraphicsView(parent)
{
    /* construct gameScene */
    gameScene = new GameScene(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setMinimumSize(500, 650);
//    scale(1.5, 1.5);
    QObject::connect(gameScene, SIGNAL(pressStart()), this, SLOT(toIndexScene()));

    /* construct indexScene */
    indexScene = new IndexScene(this);
    setScene(indexScene);
    QObject::connect(indexScene, SIGNAL(pressStart()), this, SLOT(toGameScene()));

    /* BGM music */
    bgm = new QMediaPlayer();
    playList = new QMediaPlaylist();
    playList->addMedia(QUrl("qrc:/sounds/sounds/BGM.wav"));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    bgm->setPlaylist(playList);
    bgm->play();  //-- mute when test

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

void Game::restart()
{
    init();
}

void Game::toGameScene()
{
    gameScene->init();
    setScene(gameScene);
    emit toGame();
}

void Game::toIndexScene()
{
    indexScene->resetIcon();
    setScene(indexScene);
    emit toIndex();
}

void Game::setClassMode()
{
    gameScene->setMode(GameScene::CLASSIC);
    gameScene->init();
}

void Game::setSurvivalMode()
{
    gameScene->setMode(GameScene::SURVIVAL);
    gameScene->init();
}
