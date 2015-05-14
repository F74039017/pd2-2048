#include "IndexScene.h"
#define dbName "rank.db"
#define tbName "rank"
#include "Game.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

IndexScene::IndexScene(QObject *parent)
    :QGraphicsScene(parent)
{
    indexBG = new QGraphicsPixmapItem(QPixmap(":/images/images/index_bg.png"));
    indexBG->setZValue(-1);
    addItem(indexBG);
    setSceneRect(0,0,500,650);

    /* start icon */
    startIcon = new Icon(Icon::START);
    startIcon->setScale(0.3);
    startIcon->setPos(150, 350);
    addItem(startIcon);

    /* rank icon */
    rankIcon = new Icon(Icon::RANK);
    rankIcon->setScale(0.3);
    rankIcon->setPos(150, 475);
    addItem(rankIcon);

    /* rect init */
    int w, h;
    w = startIcon->boundingRect().width()*0.3;
    h = startIcon->boundingRect().height()*0.3;
    startIconRect = new QRect(150, 350, w, h);
    rankIconRect = new QRect(150, 475, w, h);
//    qDebug() << *startIconRect << " " << *rankIconRect;

}

void IndexScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressStart();
}
