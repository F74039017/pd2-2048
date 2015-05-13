#ifndef GAME
#define GAME

#include <QGraphicsView>
#include "GameScene.h"

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game();
    void init();
    void setUserName(QString name);
    QString getuserName();

private:
    QSqlDatabase db;
    GameScene* gameScene;
    QString userName;



};

#endif // GAME

