#ifndef GAME
#define GAME

#include <QGraphicsView>
#include "GameScene.h"
#include "IndexScene.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "GameScene.h"

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game(QWidget * parent = 0);
    void init();
    void setUserName(QString name);
    QString getuserName();

signals:
    void toGame();
    void toIndex();

public slots:
    void restart();
    void toGameScene();
    void toIndexScene();
    void setClassMode();
    void setSurvivalMode();

private:
    QSqlDatabase db;
    GameScene* gameScene;
    IndexScene *indexScene;
    QString userName;
    QMediaPlayer *bgm;
    QMediaPlaylist *playList;

};

#endif // GAME

