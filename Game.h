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

class Game: public QGraphicsView{
    Q_OBJECT

public:
    Game();
    void start();
    void addsquares();
    void keyPressEvent(QKeyEvent *event);

private:
    QGraphicsScene * scene;
    QGraphicsRectItem *rect;
    QGraphicsSimpleTextItem *title;
    Square *squares[4][4];
    bool pressed;
    bool hasMoved;
    int addnum;

    int checkend();
    void gameover();
    void updateExist();
    void combine(int dir);

};

#endif // GAME

