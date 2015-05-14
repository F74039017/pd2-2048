#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QColor>
#include <QKeyEvent>
#include <cstdlib>
#include <stack>
#include "Square.h"
#include <QtSql>
using namespace std;

class GameScene: public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject *parent=0);
    void addsquares();
    void keyPressEvent(QKeyEvent *event);
    void init();

private:
    QGraphicsPixmapItem *gameBG;
    QGraphicsPixmapItem *title;
    QGraphicsSimpleTextItem *scoreLabel;
    QGraphicsSimpleTextItem *score;
    QGraphicsRectItem *gameoverBG;
    QGraphicsSimpleTextItem *gameoverLabel;
    Square *squares[4][4];
    int recordNum;
    bool pressed;
    bool hasMoved;
    bool theEnd;
    int addnum;
    int addValue;   // record the value add last time

    int checkend();
    void gameover();
    void updateExist();
    void combine(int dir);
    void addScore();
};

#endif // GAMESCENE_H
