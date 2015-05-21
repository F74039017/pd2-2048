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
#include "Square.h"
#include <QtSql>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "Icon.h"
#include <QTimer>

using namespace std;

class GameScene: public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode{CLASSIC, SURVIVAL, XTILE};
    GameScene(QObject *parent=0);
    void addsquares();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void init();
    void resetIcon();
    void setMode(GameScene::Mode mode);

signals:
    void pressStart();

public slots:
    void endAnimation();
    void countDown();

private:
    QGraphicsPixmapItem *gameBG;
    QGraphicsPixmapItem *title;
    QGraphicsSimpleTextItem *scoreLabel;
    QGraphicsSimpleTextItem *score;
    QGraphicsRectItem *gameoverBG;
    QGraphicsSimpleTextItem *gameoverLabel;
    QGraphicsSimpleTextItem *gameoverScoreLabel;
    QGraphicsSimpleTextItem *gameoverScore;
    QGraphicsSimpleTextItem *bestScoreLabel;
    QGraphicsSimpleTextItem *bestScore;
    Square *squares[4][4];
    int recordNum;
    bool pressed;
    bool hasMoved;
    bool theEnd;
    int addnum;
    int addValue;
    bool isAnimation;
    Icon *backIcon;
    Icon *againIcon;
    QRect *againIconRect;
    QRect *backIconRect;
    QParallelAnimationGroup *group;
    bool isWin;
    QTimer *timer;
    QGraphicsSimpleTextItem *timeLabel;
    GameScene::Mode mode;


    int checkend();
    void gameover();
    void updateExist();
    void combine(int dir);
    void addScore();
    void startAnimation();
};

#endif // GAMESCENE_H
