#include "Game.h"
#include <QDebug>

Game::Game()
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    scene->setBackgroundBrush(QPixmap(":/images/images/cloud.jpeg"));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(500,650);
    scene->setSceneRect(0,0,500,650);

    /* add line */
    scene->addLine(0, 525, 600, 525);   // horizon
    scene->addLine(0, 400, 600, 400);
    scene->addLine(0, 275, 600, 275);
    scene->addLine(0, 150, 600, 150);
    scene->addLine(125, 150, 125, 650); //vertical
    scene->addLine(250, 150, 250, 650);
    scene->addLine(375, 150, 375, 650);

    /* add title */
    title = new QGraphicsSimpleTextItem("2048");
    title->setPos(30, 20);
    title->setBrush(QBrush(QColor(0, 0, 255)));
    QFont titleFont("Times", 50, QFont::Bold);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, 15);
    title->setFont(titleFont);
    scene->addItem(title);

    /* add number */
    for(int i=0; i<4; i++)  // temp to show all squares in the window
        for(int j=0; j<4; j++)
        {
            squares[i][j] = new Square();
            squares[i][j]->setValue(0);
            squares[i][j]->setcor(i, j);
            squares[i][j]->setPos(15+125*j, 180+125*i);         // relocate the pos for image
            squares[i][j]->setFont(QFont("Times", 35, QFont::Bold)); // no need in image
            scene->addItem(squares[i][j]);
        }

    /* add num */
    addnum = 2;
}

void Game::start()
{
    addsquares();
}

void Game::addsquares()
{
    int randnum;
    int row;
    int col;
    int cnt=0;
    qDebug() << "add squares" << endl;
    do  // set two new square
    {
        randnum = rand()%16;
        row = randnum/4;
        col = randnum%4;
        if(squares[row][col]->isExist())
            continue;
        qDebug() << row << " " << col << endl;
        squares[row][col]->setExist(true);
        randnum = rand()%2;
        if(randnum)
            squares[row][col]->setValue(2);
        else
            squares[row][col]->setValue(4);
        cnt++;
//        qDebug() << "add new squares" << endl;
    }
    while(cnt!=addnum);

}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up)  // combine squares
        combine(1);
    else if(event->key() == Qt::Key_Down)
        combine(2);
    else if(event->key() == Qt::Key_Left)
        combine(3);
    else if(event->key() == Qt::Key_Right)
        combine(4);
    addnum = checkend();
    qDebug() << "addnum: " << addnum << endl;
    if(!hasMoved && !addnum)
        gameover();
    if(hasMoved)
        addsquares();
}

int Game::checkend()    // 2=>normal 1=>left-one 0=>end
{
    int cnt=0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            if(squares[i][j]->isExist())
                cnt++;
    if(16-cnt>1)
        return 2;
    else
        return 16-cnt;
}

void Game::gameover()   // show rank dialog in the future
{
    qDebug() << "gameover" << endl;
}

void Game::updateExist()
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            if(squares[i][j]->getValue())
                squares[i][j]->setExist(true);
            else
                squares[i][j]->setExist(false);
        }

}

void Game::combine(int dir) // 1->up 2->down 3->left 4->right
{
    hasMoved = false;
    if(dir==1)  // up
    {
        for(int i=0; i<4; i++)
        {
            stack<int> s;

            /* merge list */
            int mergedlast = false;
            for(int j=0; j<4; j++)
            {
                if(squares[j][i]->isExist())
                {
                    if(j!=s.size())   // size-1 is the final pos for up and left, not push size()
                        hasMoved = true;
                    if(!mergedlast && s.size()>=1) // merge check
                    {
//                        qDebug() << "in merge check" << endl;
                        int a = s.top();
//                        qDebug() << "last number" << a << endl;
                        int b = squares[j][i]->getValue();
//                        qDebug() << "now" << b << endl;
                        if(a == b)
                        {
//                            qDebug() << "pop " << s.top() << endl;
                            s.pop();
                            s.push(a*2);
//                            qDebug() << "push " << s.top() << endl;
                            mergedlast = true;
                            hasMoved = true;
                        }
                        else
                        {
                            s.push(b);
                            mergedlast = false;
                        }
                    }
                    else    // push square
                    {
                        s.push(squares[j][i]->getValue());
                        mergedlast = false;
                    }
                    squares[j][i]->setValue(0); // reset value
                }
            }
            while(!s.empty())   // update merge list
            {
//                qDebug() << s.top() << " ";
                squares[s.size()-1][i]->setValue(s.top());
                s.pop();
            }
//            qDebug() << "----" << endl;
        }
    }
    else if(dir==2)  // down
    {
        for(int i=3; i>=0; i--)
        {
            stack<int> s;

            /* merge list */
            int mergedlast = false;
            for(int j=3; j>=0; j--)
            {
                if(squares[j][i]->isExist())
                {
                    if(j!=4-s.size()-1)
                        hasMoved = true;
                    if(!mergedlast && s.size()>=1) // merge check
                    {
//                        qDebug() << "in merge check" << endl;
                        int a = s.top();
//                        qDebug() << "last number" << a << endl;
                        int b = squares[j][i]->getValue();
//                        qDebug() << "now" << b << endl;
                        if(a == b)
                        {
//                            qDebug() << "pop " << s.top() << endl;
                            s.pop();
                            s.push(a*2);
//                            qDebug() << "push " << s.top() << endl;
                            mergedlast = true;
                            hasMoved = true;
                        }
                        else
                        {
                            s.push(b);
                            mergedlast = false;
                        }
                    }
                    else    // push square
                    {
                        s.push(squares[j][i]->getValue());
                        mergedlast = false;
                    }
                    squares[j][i]->setValue(0); // reset value
                }
            }
            while(!s.empty())   // update merge list
            {
//                qDebug() << s.top() << " ";
                squares[4-s.size()][i]->setValue(s.top());
                s.pop();
            }
//            qDebug() << "----" << endl;
        }
    }
    else if(dir==3)  // left
    {
        for(int i=0; i<4; i++)
        {
            stack<int> s;

            /* merge list */
            int mergedlast = false;
            for(int j=0; j<4; j++)
            {
                if(squares[i][j]->isExist())
                {
                    if(j!=s.size())   // size-1 is the final pos for up and left, not push size()
                        hasMoved = true;
                    if(!mergedlast && s.size()>=1) // merge check
                    {
//                        qDebug() << "in merge check" << endl;
                        int a = s.top();
//                        qDebug() << "last number" << a << endl;
                        int b = squares[i][j]->getValue();
//                        qDebug() << "now" << b << endl;
                        if(a == b)
                        {
//                            qDebug() << "pop " << s.top() << endl;
                            s.pop();
                            s.push(a*2);
//                            qDebug() << "push " << s.top() << endl;
                            mergedlast = true;
                            hasMoved = true;
                        }
                        else
                        {
                            s.push(b);
                            mergedlast = false;
                        }
                    }
                    else    // push square
                    {
                        s.push(squares[i][j]->getValue());
                        mergedlast = false;
                    }
                    squares[i][j]->setValue(0); // reset value
                }
            }
            while(!s.empty())   // update merge list
            {
//                qDebug() << s.top() << " ";
                squares[i][s.size()-1]->setValue(s.top());
                s.pop();
            }
//            qDebug() << "----" << endl;
        }
    }
    else if(dir==4)  // right
    {
        for(int i=3; i>=0; i--)
        {
            stack<int> s;

            /* merge list */
            int mergedlast = false;
            for(int j=3; j>=0; j--)
            {
                if(squares[i][j]->isExist())
                {
                    if(j!=4-s.size()-1)
                        hasMoved = true;
                    if(!mergedlast && s.size()>=1) // merge check
                    {
//                        qDebug() << "in merge check" << endl;
                        int a = s.top();
//                        qDebug() << "last number" << a << endl;
                        int b = squares[i][j]->getValue();
//                        qDebug() << "now" << b << endl;
                        if(a == b)
                        {
//                            qDebug() << "pop " << s.top() << endl;
                            s.pop();
                            s.push(a*2);
//                            qDebug() << "push " << s.top() << endl;
                            mergedlast = true;
                            hasMoved = true;
                        }
                        else
                        {
                            s.push(b);
                            mergedlast = false;
                        }
                    }
                    else    // push square
                    {
                        s.push(squares[i][j]->getValue());
                        mergedlast = false;
                    }
                    squares[i][j]->setValue(0); // reset value
                }
            }
            while(!s.empty())   // update merge list
            {
//                qDebug() << s.top() << " ";
                squares[i][4-s.size()]->setValue(s.top());
                s.pop();
            }
//            qDebug() << "----" << endl;
        }
    }
    updateExist();
}
