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
    int recordNum;
    QGraphicsSimpleTextItem *title;
    Square *squares[4][4];
    bool pressed;
    bool hasMoved;
    int addnum;
    QGraphicsSimpleTextItem *scoreLabel;
    QGraphicsSimpleTextItem *score;
    int addValue;   // record the value add last time
    bool theEnd;
    QGraphicsRectItem *gameoverBG;
    QGraphicsSimpleTextItem *gameoverLabel;

    int checkend();
    void gameover();
    void updateExist();
    void combine(int dir);
    void addScore();
};

#endif // GAMESCENE_H