#include "Square.h"

Square::Square(QGraphicsItem * parent)    // reimplement when change to pixitem
        :QGraphicsPixmapItem(parent)
{
    init();
}

void Square::setValue(int x)
{
    value = x;
    updatePixmap();
//    setText(QString::number(value));    // temp for simpletext class
}

int Square::getValue()
{
    return value;
}

void Square::setExist(bool flag)
{
    exist = flag;
    if(!flag)
        hide();
    else
        show();
}

bool Square::isExist()
{
    return exist;
}

void Square::setcor(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Square::getX()
{
    return x;
}

int Square::getY()
{
    return y;
}

void Square::init()
{
    exist = false;
    value = 0;
}

void Square::updatePixmap()
{
    switch(value)
    {
        case 2:
            setPixmap(QPixmap(":/images/images/square2.png"));
            break;
        case 4:
            setPixmap(QPixmap(":/images/images/square4.png"));
            break;
        case 8:
            setPixmap(QPixmap(":/images/images/square8.png"));
            break;
        case 16:
            setPixmap(QPixmap(":/images/images/square16.png"));
            break;
        case 32:
            setPixmap(QPixmap(":/images/images/square32.png"));
            break;
        case 64:
            setPixmap(QPixmap(":/images/images/square64.png"));
            break;
        case 128:
            setPixmap(QPixmap(":/images/images/square128.png"));
            break;
        case 256:
            setPixmap(QPixmap(":/images/images/square256.png"));
            break;
        case 512:
            setPixmap(QPixmap(":/images/images/square512.png"));
            break;
        case 1024:
            setPixmap(QPixmap(":/images/images/square1024.png"));
            break;
        case 2048:
            setPixmap(QPixmap(":/images/images/square2048.png"));
            break;
    }
}
