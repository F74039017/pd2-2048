#ifndef INDEXSCENE_H
#define INDEXSCENE_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "Icon.h"

class IndexScene: public QGraphicsScene
{
    Q_OBJECT

public:
    IndexScene(QObject *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void pressStart();

private:
    QGraphicsPixmapItem *indexBG;
    Icon *startIcon;
    Icon *rankIcon;

    QRect *startIconRect;
    QRect *rankIconRect;
};

#endif // INDEXSCENE_H
