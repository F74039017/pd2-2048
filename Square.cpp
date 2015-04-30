#include "Square.h"

Square::Square()
{
    init();
}

Square::Square(const QString & text, QGraphicsItem * parent)    // reimplement when change to pixitem
        :QGraphicsSimpleTextItem(text, parent)
{
    init();
}

void Square::setValue(int x)
{
    value = x;
    setText(QString::number(value));    // temp for simpletext class
}

int Square::getValue()
{
    return value;
}

void Square::setExist(bool flag)
{
    exist = flag;
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
