#ifndef GAME
#define GAME

#include <QGraphicsView>
#include "GameScene.h"
#include "IndexScene.h"

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game(QWidget * parent = 0);
    void init();
    void setUserName(QString name);
    QString getuserName();

public slots:
    void restart();
    void toGameScene();

private:
    QSqlDatabase db;
    GameScene* gameScene;
    IndexScene *indexScene;
    QString userName;

};

#endif // GAME

