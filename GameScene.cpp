#include "GameScene.h"
#include <QDebug>
#include <cstdlib>
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
    bestScoreLabel = new QGraphicsSimpleTextItem("Your Best:");
    bestScoreLabel->setPos(85, 350);
    bestScoreLabel->setBrush(QColor(Qt::black));
    bestScoreLabel->setPen(gameoverPen);
    bestScoreLabel->setFont(gameoverFont);
    addItem(bestScoreLabel);
    gameoverScore = new QGraphicsSimpleTextItem("0");
    gameoverScore->setPos(310, 250);
    gameoverScore->setBrush(QColor(Qt::black));
    gameoverScore->setPen(gameoverPen);
    gameoverScore->setFont(gameoverFont);
    addItem(gameoverScore);
    bestScore = new QGraphicsSimpleTextItem("0");
    bestScore->setPos(310, 350);
    bestScore->setBrush(QColor(Qt::black));
    bestScore->setPen(gameoverPen);
    bestScore->setFont(gameoverFont);
    addItem(bestScore);

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

    /* time (survive) mdoe */
    timer = new QTimer(this);
    timeLabel = new QGraphicsSimpleTextItem("15");
    timeLabel->setPos(400, 20);
    timeLabel->setBrush(QBrush(QColor(Qt::yellow)));
    QFont timeLabelFont("URW Chancery L", 25);
    timeLabelFont.setItalic(true);
    timeLabel->setFont(timeLabelFont);
    addItem(timeLabel);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(countDown()));

    /* init mode */
    mode = GameScene::CLASSIC;
}

void GameScene::init()
{
    /* get number of rank */
    QSqlQuery qry;
    qry.exec(QString("SELECT COUNT(*) FROM %1").arg(tbName));
    qry.next();
//    qDebug() << "row now is " << qry.value(0).toString();
    recordNum = qry.value(0).toInt();
//    qDebug() << "update new recordNum = " << recordNum;


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
    if(mode == XTILE)
        addnum = 3;
    else
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
    isCont = false;
    gameoverBG->hide();
    gameoverBG->setZValue(1);
    gameoverLabel->hide();
    gameoverLabel->setZValue(1);
    gameoverScoreLabel->hide();
    gameoverScoreLabel->setZValue(1);
    bestScoreLabel->hide();
    bestScoreLabel->setZValue(1);
    gameoverScore->hide();
    gameoverScore->setZValue(1);
    bestScore->hide();
    bestScore->setZValue(1);
    againIcon->hide();
    againIcon->setZValue(1);
    backIcon->hide();
    backIcon->setZValue(1);
    backIcon->setSoundFlag(false);
    againIcon->setSoundFlag(false);

    /* reset time */
    if(mode == GameScene::SURVIVAL)
    {
        timeLabel->show();
        timeLabel->setText("15");
        timer->start(1000);
    }
    else
    {
        timeLabel->hide();
        timer->stop();
    }

    /* get userName */
    userName = dynamic_cast<Game*>(parent())->getuserName();


    addsquares();
}

void GameScene::resetIcon()
{
    backIcon->setImage(backIcon->getType());
    againIcon->setImage(againIcon->getType());
}

void GameScene::setMode(GameScene::Mode mode)
{
    this->mode = mode;
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

    if(mode==XTILE && addnum==3)    // add Xtile
        squares[row][col]->setValue(-1);
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
        if(!Mainwindow::soundMute)
            againIcon->playClickSound();
        if(!isWin)
            init();
        else
        {
            isCont = true;
            cont();
        }
    }
    else if(backIconRect->contains(event->scenePos().toPoint()) && theEnd)
    {
        if(!Mainwindow::soundMute)
            backIcon->playClickSound();
        if(isWin)
            insertRank();
        emit pressBack();
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
            if(squares[i][j]->getValue()==2048 && !isCont)   // win check, no use when cont
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
    if(mode == GameScene::SURVIVAL)
        timer->stop();

    /* insert user and score to database */
    if(!isWin)
        insertRank();

    gameoverScore->setText(score->text());
    QSqlQuery qry;
    if(qry.exec(QString("SELECT score FROM %1 WHERE name GLOB '%2' ORDER BY score DESC").arg(tbName, userName)))
    {
        qry.next();
        bestScore->setText(qry.value(0).toString());
    }
    else
        qDebug() << "Fail to get best score";

    if(isWin)
    {
        againIcon->setType(Icon::CONT);
        gameoverLabel->setText("You Win"), gameoverLabel->setPos(100, 80);
    }
    else
    {
        againIcon->setType(Icon::AGAIN);
        gameoverLabel->setText("Game Over"), gameoverLabel->setPos(55, 80);
    }

    /* show gameover panel and set flag */
    gameoverBG->show();
    gameoverLabel->show();
    gameoverScoreLabel->show();
    bestScoreLabel->show();
    gameoverScore->show();
    bestScore->show();
    againIcon->show();
    backIcon->show();
    againIcon->setSoundFlag(true);
    backIcon->setSoundFlag(true);
    theEnd = true;
//    qDebug() << "gameover" << endl;
}

void GameScene::updateExist()   // call after move => hide and show squares
{
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
        {
            if(squares[i][j]->getValue())   // value != 0
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
    addTime = 0;
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
                if(cur==last && cur!=Square::maxValue)
                {
                    squares[id][i]->setValue(cur*2), last=0, addValue += cur*2;
                    addTime += (cur>=16)? 2: 0;
                }
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
                if(cur==last && cur!=Square::maxValue)
                {
                    squares[id][i]->setValue(cur*2), last=0, addValue += cur*2;
                    addTime += (cur>=16)? 2: 0;
                }
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
                if(cur==last && cur!=Square::maxValue)
                {
                    squares[i][id]->setValue(cur*2), last=0, addValue += cur*2;
                    addTime += (cur>=16)? 2: 0;
                }
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
                if(cur==last && cur!=Square::maxValue)
                {
                    squares[i][id]->setValue(cur*2), last=0, addValue += cur*2;
                    addTime += (cur>=16)? 2: 0;
                }
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
    /* survival mode increase 2 second when merged point>=16 */
    if(mode==GameScene::SURVIVAL)
        timeLabel->setText(QString::number(timeLabel->text().toInt()+addTime));

    /* survival mode increase 2*value for rank */
//    qDebug() << addValue;
    if(mode==GameScene::SURVIVAL)
        addValue <<= 1;
    else if(mode==GameScene::XTILE)
        addValue *= 1.5;
//    qDebug() << addValue;
    int newScore = score->text().toInt()+addValue;
    score->setText(QString::number(newScore));
}

void GameScene::startAnimation()
{
    isAnimation = true; // block input
    group->start();
}

void GameScene::cont()
{
    gameoverBG->hide();
    gameoverLabel->hide();
    gameoverScoreLabel->hide();
    bestScoreLabel->hide();
    gameoverScore->hide();
    bestScore->hide();
    againIcon->hide();
    backIcon->hide();
    againIcon->setSoundFlag(false);
    backIcon->setSoundFlag(false);
    theEnd = false;
    isWin = false;
}

void GameScene::insertRank()
{
    QSqlQuery qry;
    if(!qry.exec(QString("INSERT INTO %1 VALUES (%2, '%3', %4)").arg(tbName, QString::number(recordNum), userName, score->text())));
        qDebug() << qry.lastError().text();
}

void GameScene::endAnimation()
{
//    squares[0][0]->setValue(2048);  //-- test win

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

void GameScene::countDown()
{
    int nextTime = timeLabel->text().toInt()-1;
    if(nextTime == -1)
        gameover();
    else
        timeLabel->setText(QString::number(nextTime));
}
