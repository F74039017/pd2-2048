#ifndef GAME
#define GAME

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
using namespace std;
#include "Square.h"
#include <QtSql>

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game();
    void init();
    void addsquares();
    void keyPressEvent(QKeyEvent *event);
    void setUserName(QString name);

private:
    int recordNum;
    QString userName;
    QGraphicsScene *gameScene;
    QGraphicsScene *indexScene; // use setScene method to replace the scene
    QGraphicsRectItem *rect;
    QGraphicsSimpleTextItem *title;
    Square *squares[4][4];
    bool pressed;
    bool hasMoved;
    int addnum;
    QGraphicsSimpleTextItem *scoreLabel;
    QGraphicsSimpleTextItem *score;
    int addValue;   // record the value add last time
    QSqlDatabase db;
    bool theEnd;


    int checkend();
    void gameover();
    void updateExist();
    void combine(int dir);
    void addScore();

};

#endif // GAME

