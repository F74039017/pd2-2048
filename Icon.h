#ifndef ICON_H
#define ICON_H
#include <QGraphicsPixmapItem>
#include <QSoundEffect>

class Icon : public QGraphicsPixmapItem
{
public:
    enum Type{START, RANK, BACK, AGAIN};
    Icon(Icon::Type type, QGraphicsItem * parent=0);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void setImage(Icon::Type type);
    Icon::Type getType();
    void playClickSound();

private:
    Type type;
    QSoundEffect *inSound;
    QSoundEffect *clickSound;
};

#endif // ICON_H
