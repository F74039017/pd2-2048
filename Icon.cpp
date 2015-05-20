#include "Icon.h"
#include <QDebug>

Icon::Icon(Icon::Type type, QGraphicsItem * parent)
    :QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/rank_icon.png"));
    setAcceptHoverEvents(true);
    this->type = type;
    setImage(type);

    /* enter icon sound */
    inSound = new QSoundEffect();
    inSound->setSource(QUrl("qrc:/sounds/sounds/icon_in.wav"));
    inSound->setVolume(0.8);

    /* click icon sound */
    clickSound = new QSoundEffect();
    clickSound->setSource(QUrl("qrc:/sounds/sounds/icon_click.wav"));
}

void Icon::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    inSound->play();

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

Icon::Type Icon::getType()
{
    return type;
}

void Icon::playClickSound()
{
    clickSound->play();
}


