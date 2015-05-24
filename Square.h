#ifndef SQUARE
#define SQUARE

#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QPropertyAnimation>

class Square: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY (QPointF pos READ pos WRITE setPos)

public:
    static const int maxValue = 2048;
    Square(QGraphicsItem * parent = 0);
    void setValue(int value);
    int getValue();
    void setExist(bool flag);
    bool isExist();
    void setcor(int x, int y);
    int getX();
    int getY();
    QPropertyAnimation *getAnimation();
    void setMoveEnd(QPointF e);
    void recoverPos();
    void setRecoverPoint();

private:
    int value;
    bool exist;
    int x;
    int y;
    QPointF recoverPoint;
    QPropertyAnimation *move;

    void init();
    void updatePixmap();
};

#endif // SQUARE

