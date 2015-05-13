#include "GameScene.h"
#include <QDebug>
#include <cstdlib>
#define dbName "rank.db"
#define tbName "rank"
#include "Game.h"

GameScene::GameScene(QObject *parent)
    :QGraphicsScene(parent)
{
    setBackgroundBrush(QPixmap(":/images/images/cloud.jpeg"));
    setSceneRect(0,0,500,650);
    /* add line */
    addLine(0, 525, 600, 525);   // horizon
    addLine(0, 400, 600, 400);
    addLine(0, 275, 600, 275);
    addLine(0, 150, 600, 150);
    addLine(125, 150, 125, 650); //vertical
    addLine(250, 150, 250, 650);
    addLine(375, 150, 375, 650);

    /* add title */
    title = new QGraphicsSimpleTextItem("2048");
    title->setPos(30, 20);
    title->setBrush(QBrush(QColor(255, 10, 10)));
    QFont titleFont("Times", 50, QFont::Bold);
    titleFont.setLetterSpacing(QFont::AbsoluteSpacing, 15);
    title->setFont(titleFont);
    addItem(title);

    /* Score */
    scoreLabel = new QGraphicsSimpleTextItem("Score:");
    scoreLabel->setPos(275, 35);
    scoreLabel->setBrush(QBrush(QColor(220, 70, 70)));
    QFont scoreLabelFont("URW Chancery L", 25);
    scoreLabelFont.setItalic(true);
    scoreLabelFont.setUnderline(true);
    scoreLabel->setFont(scoreLabelFont);
    addItem(scoreLabel);
    score = new QGraphicsSimpleTextItem("0");
    score->setPos(350, 80);
    score->setBrush(QBrush(QColor(220, 70, 70)));
    QFont scoreFont("URW Chancery L", 25);
    scoreFont.setItalic(true);
    score->setFont(scoreFont);
    addItem(score);

    /* add squares */
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            squares[i][j] = new Square(QPixmap(":/images/images/square2.png"));
            squares[i][j]->setScale(0.25);
            squares[i][j]->setcor(i, j);
            squares[i][j]->setPos(125*j,150+125*i);         // relocate the pos for image
            //squares[i][j]->setFont(QFont("Times", 35, QFont::Bold)); // no need in image
            addItem(squares[i][j]);
        }

    /* GameOver */
    gameoverBG = new QGraphicsRectItem(0, 0, 500, 650);
    gameoverBG->setBrush(QBrush(QColor(128, 128, 128)));
    gameoverBG->setOpacity(0.85);
    gameoverBG->setPen(Qt::NoPen);
    addItem(gameoverBG);
    gameoverBG->hide();
    gameoverLabel = new QGraphicsSimpleTextItem("Game Over");
    gameoverLabel->setPos(55, 80);
//    gameoverLabel->setBrush(QBrush(QColor(220, 70, 70)));
    QFont gameoverLabelFont("URW Chancery L", 55);
    gameoverLabelFont.setItalic(true);
    gameoverLabelFont.setBold(true);
    gameoverLabelFont.setLetterSpacing(QFont::AbsoluteSpacing, 10);
    gameoverLabel->setFont(gameoverLabelFont);
    addItem(gameoverLabel);
    gameoverLabel->hide();
}

void GameScene::init()
{
    QSqlQuery qry;
    qry.exec(QString("SELECT COUNT(*) FROM %1").arg(tbName));
    qry.next();
//    qDebug() << "row now is " << qry.value(0).toString();
    recordNum = qry.value(0).toInt();

    /* init squares */
    for(int i=0; i<4; i++)  // temp to show all squares in the window
        for(int j=0; j<4; j++)
        {
            squares[i][j]->setValue(0);
            squares[i][j]->setExist(false);
        }

    /* init score */
    score->setText("0");

    /* init num */
    addnum = 2;

    /* init gameOver flag */
    theEnd = false;

    addsquares();
}

void GameScene::addsquares()
{
    int randnum;
    int row;
    int col;
    int cnt=0;
//    qDebug() << "add squares" << endl;
    do  // set two new square
    {
        randnum = rand()%16;
        row = randnum/4;
        col = randnum%4;
        if(squares[row][col]->isExist())
            continue;
//        qDebug() << row << " " << col << endl;
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

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(theEnd)
        return;

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
    if(event->key() == Qt::Key_R)
        init();
}

int GameScene::checkend()    // 2=>normal 1=>left-one 0=>end
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

void GameScene::gameover()   // show rank dialog in the future
{
    gameoverBG->show();
    gameoverLabel->show();
    theEnd = true;
//    qDebug() << "gameover" << endl;
    recordNum++;
    QSqlQuery qry;
    QString userName = dynamic_cast<Game*>(parent())->getuserName();
    if(!qry.exec(QString("INSERT INTO %1 VALUES (%2, '%3', %4)").arg(tbName, QString::number(recordNum), userName, score->text())));
        qDebug() << qry.lastError().text();
}

void GameScene::updateExist()
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

void GameScene::combine(int dir) // 1->up 2->down 3->left 4->right
{
    addValue = 0;   // addValue init to 0
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
                            addValue += a*2;
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
                            addValue += a*2;
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
                            addValue += a*2;
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
                            addValue += a*2;
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
    addScore(); // update score
}

void GameScene::addScore()
{
    int newScore = score->text().toInt()+addValue;
    score->setText(QString::number(newScore));
}

