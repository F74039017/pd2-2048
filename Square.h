#ifndef SQUARE
#define SQUARE

#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>

class Square: public QObject, public QGraphicsPixmapItem    // change pixitem
{
    Q_OBJECT
public:
    Square();
    Square(const QPixmap & pixmap, QGraphicsItem * parent = 0);

    void setValue(int value);
    int getValue();
    void setExist(bool flag);
    bool isExist();
    void setcor(int x, int y);
    int getX();
    int getY();


//public slots:
//    void setExist(bool flag);

private:
    int value;
    bool exist;
    int x;
    int y;

    void init();
};

#endif // SQUARE

