#ifndef ICON_H
#define ICON_H
#include <QGraphicsPixmapItem>

class Icon : public QGraphicsPixmapItem
{
public:
    enum Type{START, RANK, BACK, AGAIN};
    Icon(Icon::Type type, QGraphicsItem * parent=0);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void setImage(Icon::Type type);
    Icon::Type getType();

private:
    Type type;
};

#endif // ICON_H
