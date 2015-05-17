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
    w = startIcon->boundingRect().width()*0.23;
    h = startIcon->boundingRect().height()*0.23;
    backIconRect = new QRect(300, 550, w, h);
//    qDebug() << *startIconRect << " " << *rankIconRect;

    /* add rankBG */
    rankBG = new QGraphicsPixmapItem(QPixmap(":/images/images/rank_border.png"));
    rankBG->setScale(0.65);
    rankBG->setPos(25, 50);
    rankBG->setZValue(1);
    addItem(rankBG);
    rankBG->hide();
    rankon = false;

    /* add backIcon */
    backIcon = new Icon(Icon::BACK);
    backIcon->setScale(0.23);
    backIcon->setPos(300, 550);
    backIcon->setZValue(2);
    addItem(backIcon);
    backIcon->hide();

    /* init rank id */
    QFont rankFont("URW Chancery L", 25);
    rankFont.setBold(true);
    for(int i=0; i<10; i++)
    {
        rankID[i] = new QGraphicsSimpleTextItem(QString("%1.").arg(i+1));
        rankID[i]->setZValue(2);
        rankID[i]->setPos(60, 162+i*38.5);
        rankID[i]->setFont(rankFont);
        addItem(rankID[i]);
        rankID[i]->hide();
    }

    /* init rank name */
    for(int i=0; i<10; i++)
    {
        rankName[i] = new QGraphicsSimpleTextItem(QString("------"));
        rankName[i]->setZValue(2);
        rankName[i]->setPos(110, 162+i*38.5);
        rankName[i]->setFont(rankFont);
        addItem(rankName[i]);
        rankName[i]->hide();
    }

    /* init rank score */
    for(int i=0; i<10; i++)
    {
        rankScore[i] = new QGraphicsSimpleTextItem(QString("---"));
        rankScore[i]->setZValue(2);
        rankScore[i]->setPos(320, 162+i*38.5);
        rankScore[i]->setFont(rankFont);
        addItem( rankScore[i]);
        rankScore[i]->hide();
    }

}

void IndexScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(startIconRect->contains(event->scenePos().toPoint()) && !rankon)
        emit pressStart();
    else if(rankIconRect->contains(event->scenePos().toPoint()) && !rankon)
        showRank();
    else if(backIconRect->contains(event->scenePos().toPoint()) && rankon)
        hideRank();
}

void IndexScene::showRank() // start pos bug
{
    rankon = true;
    rankBG->show();
    backIcon->show();
    for(int i=0; i<10; i++)
        rankName[i]->show(), rankID[i]->show(), rankScore[i]->show();
    updateRank();
}

void IndexScene::hideRank()
{
    rankon = false;
    rankBG->hide();
    backIcon->hide();
    backIcon->setImage(backIcon->getType());
    for(int i=0; i<10; i++)
        rankName[i]->hide(), rankID[i]->hide(), rankScore[i]->hide();
}

void IndexScene::updateRank()
{
    QSqlQuery qry;
    QString name;
    if(qry.exec(QString("SELECT name, score FROM %1 ORDER BY score DESC").arg(tbName)))
    {
        int i=0;
        while(qry.next())
        {
//            qDebug() << qry.value(0).toString() << "\t" << qry.value(1).toInt();
            rankName[i]->setText(QString("%1").arg(qry.value(0).toString()));
            rankScore[i]->setText(QString("%1").arg(qry.value(1).toString()));
            if(i==9)
                break;
            i++;
        }
    }
    else
    {
        qDebug() << qry.lastError().text();
        return;
    }
}