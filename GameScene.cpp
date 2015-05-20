#include "GameScene.h"
#include <QDebug>
#include <cstdlib>
#define dbName "rank.db"
#define tbName "rank"
#include "Game.h"
#include "Mainwindow.h"
#include <QGraphicsSceneMouseEvent>

GameScene::GameScene(QObject *parent)
    :QGraphicsScene(parent)
{
    /* set game background */
    gameBG = new QGraphicsPixmapItem(QPixmap(":/images/images/game_bg_light.png"));
    gameBG->setScale(0.731);
    gameBG->setZValue(-1);
    addItem(gameBG);
    setSceneRect(0,0,500,650);

    /* add line */
    QPen pen = QPen(QColor(Qt::white));
    addLine(0, 525, 600, 525, pen);   // horizon
    addLine(0, 400, 600, 400, pen);
    addLine(0, 275, 600, 275, pen);
    addLine(0, 150, 600, 150, pen);
    addLine(125, 150, 125, 650, pen); //vertical
    addLine(250, 150, 250, 650, pen);
    addLine(375, 150, 375, 650, pen);

    /* add title */
    title = new QGraphicsPixmapItem(QPixmap(":/images/images/2048_title_in.png"));
    title->setPos(-40, -10);
    title->setScale(0.35);
    addItem(title);

    /* Score */
    scoreLabel = new QGraphicsSimpleTextItem("Score:");
    scoreLabel->setPos(285, 35);
//    scoreLabel->setBrush(QBrush(QColor(220, 70, 70)));
    scoreLabel->setBrush(QBrush(QColor(Qt::white)));
    QFont scoreLabelFont("URW Chancery L", 25);
    scoreLabelFont.setItalic(true);
    scoreLabelFont.setUnderline(true);
    scoreLabel->setFont(scoreLabelFont);
    addItem(scoreLabel);
    score = new QGraphicsSimpleTextItem("0");
    score->setPos(360, 80);
//    score->setBrush(QBrush(QColor(220, 70, 70)));
    score->setBrush(QBrush(QColor(Qt::white)));
    QFont scoreFont("URW Chancery L", 25);
    scoreFont.setItalic(true);
    score->setFont(scoreFont);
    addItem(score);

    /* add squares */
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            squares[i][j] = new Square();
            squares[i][j]->setScale(0.25);
            squares[i][j]->setcor(i, j);
            squares[i][j]->setPos(125*j,150+125*i);
            addItem(squares[i][j]);
            squares[i][j]->hide();
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
    gameoverLabel->setBrush(QColor(Qt::black));
    QPen gameoverPen(QColor(Qt::white));
    gameoverPen.setWidth(3);
    gameoverLabel->setPen(gameoverPen);
    QFont gameoverFont("URW Chancery L", 55);
    gameoverFont.setItalic(true);
    gameoverFont.setBold(true);
    gameoverFont.setLetterSpacing(QFont::AbsoluteSpacing, 10);
    gameoverLabel->setFont(gameoverFont);
    addItem(gameoverLabel);
    gameoverLabel->hide();

    /* Gameover Score */
    gameoverScoreLabel = new QGraphicsSimpleTextItem("Your Score:");
    gameoverScoreLabel->setPos(85, 250);
    gameoverScoreLabel->setBrush(QColor(Qt::black));
    gameoverFont.setPointSize(32);
    gameoverFont.setBold(true);
    gameoverFont.setLetterSpacing(QFont::AbsoluteSpacing, 3);
    gameoverPen.setWidth(1);
    gameoverScoreLabel->setPen(gameoverPen);
    gameoverScoreLabel->setFont(gameoverFont);
    addItem(gameoverScoreLabel);
    gameoverScoreLabel->hide();
    bestScoreLabel = new QGraphicsSimpleTextItem("Your Best:");
    bestScoreLabel->setPos(85, 350);
    bestScoreLabel->setBrush(QColor(Qt::black));
    bestScoreLabel->setPen(gameoverPen);
    bestScoreLabel->setFont(gameoverFont);
    addItem(bestScoreLabel);
    bestScoreLabel->hide();
    gameoverScore = new QGraphicsSimpleTextItem("0");
    gameoverScore->setPos(310, 250);
    gameoverScore->setBrush(QColor(Qt::black));
    gameoverScore->setPen(gameoverPen);
    gameoverScore->setFont(gameoverFont);
    addItem(gameoverScore);
    gameoverScore->hide();
    bestScore = new QGraphicsSimpleTextItem("0");
    bestScore->setPos(310, 350);
    bestScore->setBrush(QColor(Qt::black));
    bestScore->setPen(gameoverPen);
    bestScore->setFont(gameoverFont);
    addItem(bestScore);
    bestScore->hide();

    /* again icon */
    againIcon = new Icon(Icon::AGAIN);
    againIcon->setScale(0.28);
    againIcon->setPos(40, 480);
    addItem(againIcon);
    againIcon->hide();

    /* back icon */
    backIcon = new Icon(Icon::BACK);
    backIcon->setScale(0.28);
    backIcon->setPos(300, 480);
    addItem(backIcon);
    backIcon->hide();

    /* rect init */
    int w, h;
    w = againIcon->boundingRect().width()*0.28;
    h = againIcon->boundingRect().height()*0.28;
    againIconRect = new QRect(40, 480, w, h);
    backIconRect = new QRect(300, 480, w, h);

    /* init group */
    group = new QParallelAnimationGroup(this);

    /* connect animation */
    QObject::connect(group, SIGNAL(finished()), this, SLOT(endAnimation()));
}

void GameScene::init()
{
    /* get number of rank */
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
    addnum = 2; // start with 2 squares

    /* isAnimation */
    isAnimation = false;

    /* init recover point of squares */
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            squares[i][j]->setRecoverPoint();

    /* init gameover */
    resetIcon();
    theEnd = false;
    isWin = false;
    gameoverBG->hide();
    gameoverLabel->hide();
    gameoverScoreLabel->hide();
    bestScoreLabel->hide();
    gameoverScore->hide();
    bestScore->hide();
    againIcon->hide();
    backIcon->hide();

    addsquares();
}

void GameScene::resetIcon()
{
    backIcon->setImage(backIcon->getType());
    againIcon->setImage(againIcon->getType());
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
    else
        return;

}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(againIconRect->contains(event->scenePos().toPoint()) && theEnd)
    {
        againIcon->playClickSound();
        init();
    }
    else if(backIconRect->contains(event->scenePos().toPoint()) && theEnd)
    {
        backIcon->playClickSound();
       emit pressStart();
    }
}

int GameScene::checkend()    // 1=>normal 0=>end
{
    int cnt=0;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            if(squares[i][j]->isExist())
                cnt++;
            if(squares[i][j]->getValue() == 2048)   // win
            {
                isWin = true;
                return 1;
            }
        }
    if(16-cnt>=1)
        return 1;
    else
        return 0;
}

void GameScene::gameover()   // show rank dialog in the future
{
    /* insert user and score to database */
    QSqlQuery qry;
    QString userName = dynamic_cast<Game*>(parent())->getuserName();
    if(!qry.exec(QString("INSERT INTO %1 VALUES (%2, '%3', %4)").arg(tbName, QString::number(recordNum), userName, score->text())));
        qDebug() << qry.lastError().text();

    gameoverScore->setText(score->text());
    if(qry.exec(QString("SELECT score FROM %1 WHERE name GLOB '%2' ORDER BY score DESC").arg(tbName, userName)))
    {
        qry.next();
        bestScore->setText(qry.value(0).toString());
    }
    else
        qDebug() << "Fail to get best score";

    if(isWin)
        gameoverLabel->setText("You Win"), gameoverLabel->setPos(100, 80);
    else
        gameoverLabel->setText("Game Over"), gameoverLabel->setPos(55, 80);

    gameoverBG->show();
    gameoverLabel->show();
    gameoverScoreLabel->show();
    bestScoreLabel->show();
    gameoverScore->show();
    bestScore->show();
    againIcon->show();
    backIcon->show();
    theEnd = true;
//    qDebug() << "gameover" << endl;
    recordNum++;
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
    if(isAnimation)
        return;

    addValue = 0;   // addValue init to 0
    hasMoved = false;

    if(dir==1)  // up
    {
        for(int i=0; i<4; i++)
        {
            int last=0;
            int id=-1;
            for(int j=0; j<4; j++)
            {
                if(!squares[j][i]->isExist())
                    continue;
                int cur = squares[j][i]->getValue();
                if(cur==last)
                    squares[id][i]->setValue(cur*2), last=0, addValue += cur*2;
                else
                    squares[++id][i]->setValue(cur), last=cur;
                if(!(id==j))
                {
                    squares[j][i]->setValue(0), hasMoved = true;
                    squares[j][i]->setMoveEnd(squares[id][i]->pos());
                    group->addAnimation(squares[j][i]->getAnimation());
                }
            }
        }
    }
    else if(dir==2)  // down
    {
        for(int i=3; i>=0; i--)
        {
            int last=0;
            int id=4;
            for(int j=3; j>=0; j--)
            {
                if(!squares[j][i]->isExist())
                    continue;
                int cur = squares[j][i]->getValue();
                if(cur==last)
                    squares[id][i]->setValue(cur*2), last=0, addValue += cur*2;
                else
                    squares[--id][i]->setValue(cur), last=cur;
                if(!(id==j))
                {
                    squares[j][i]->setValue(0), hasMoved = true;
                    squares[j][i]->setMoveEnd(squares[id][i]->pos());
                    group->addAnimation(squares[j][i]->getAnimation());
                }
            }
        }
    }
    else if(dir==3)  // left
    {
        for(int i=0; i<4; i++)
        {
            int last=0;
            int id=-1;
            for(int j=0; j<4; j++)
            {
                if(!squares[i][j]->isExist())
                    continue;
                int cur = squares[i][j]->getValue();
                if(cur==last)
                    squares[i][id]->setValue(cur*2), last=0, addValue += cur*2;
                else
                    squares[i][++id]->setValue(cur), last=cur;
                if(!(id==j))
                {
                    squares[i][j]->setValue(0), hasMoved = true;
                    squares[i][j]->setMoveEnd(squares[i][id]->pos());
                    group->addAnimation(squares[i][j]->getAnimation());
                }
            }
        }
    }
    else if(dir==4)  // right
    {
        for(int i=3; i>=0; i--)
        {
            int last=0;
            int id=4;
            for(int j=3; j>=0; j--)
            {
                if(!squares[i][j]->isExist())
                    continue;
                int cur = squares[i][j]->getValue();
                if(cur==last)
                    squares[i][id]->setValue(cur*2), last=0, addValue += cur*2;
                else
                    squares[i][--id]->setValue(cur), last=cur;
                if(!(id==j))
                {
                    squares[i][j]->setValue(0), hasMoved = true;
                    squares[i][j]->setMoveEnd(squares[i][id]->pos());
                    group->addAnimation(squares[i][j]->getAnimation());
                }
            }
        }
    }
    if(hasMoved)
        addValue += 2;
    startAnimation();
}

void GameScene::addScore()
{
    int newScore = score->text().toInt()+addValue;
    score->setText(QString::number(newScore));
}

void GameScene::startAnimation()
{
    isAnimation = true; // block input
    group->start();
}

void GameScene::endAnimation()
{
    //squares[0][0]->setValue(2048);  //-- test win

    /* after finish */
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            squares[i][j]->recoverPos();
    updateExist();
    addScore(); // update score
    group->clear();
    isAnimation = false;

    addnum = checkend();
//    qDebug() << "addnum: " << addnum << endl;

    if((!hasMoved && !addnum) || isWin)
        gameover();

    if(hasMoved)
        addsquares();
}
