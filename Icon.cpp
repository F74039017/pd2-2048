#include "Icon.h"
#include <QDebug>

Icon::Icon(Icon::Type type, QGraphicsItem * parent)
    :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/rank_icon.png"));
    setAcceptHoverEvents(true);
    this->type = type;
    setImage(type);
}

void Icon::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    switch(type)
    {
        case START:
            setPixmap(QPixmap(":/images/images/start_icon_pressed.png"));
            break;
        case RANK:
            setPixmap(QPixmap(":/images/images/rank_icon_pressed.png"));
            break;
        case BACK:
            setPixmap(QPixmap(":/images/images/back_icon_pressed.png"));
            break;
        case AGAIN:
            setPixmap(QPixmap(":/images/images/again_icon_pressed.png"));
            break;
    }
}

void Icon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setImage(type);
}

void Icon::setImage(Icon::Type type)
{
    switch(type)
    {
        case START:
            setPixmap(QPixmap(":/images/images/start_icon.png"));
            break;
        case RANK:
            setPixmap(QPixmap(":/images/images/rank_icon.png"));
            break;
        case BACK:
            setPixmap(QPixmap(":/images/images/back_icon.png"));
            break;
        case AGAIN:
            setPixmap(QPixmap(":/images/images/again_icon.png"));
            break;
    }
}


