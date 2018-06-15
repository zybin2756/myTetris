#include "myview.h"
#include "onebox.h"

#include <QIcon>
#include <QGraphicsScene>
#include <QGraphicsEffect>
#include <QPropertyAnimation>

static const qreal SPEED = 500;

myView::myView(QWidget *parent) : QGraphicsView(parent)
{
    initView();
}


//slots
void myView::startGame(){
    initGame();
}

void myView::clearFullRows(){

    for(int y = 429; y > 50; y-=20){
        QList<QGraphicsItem *> list = scene()->items(QRectF(199, y, 202, 22), Qt::ContainsItemShape);


        if(list.count() == 10){
            foreach(QGraphicsItem* item, list){
                OneBox* box = (OneBox*) item;
//                box->deleteLater();
                QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
                blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
                blurEffect->setBlurRadius(5);
                box->setGraphicsEffect(blurEffect);

                QPropertyAnimation *animation = new QPropertyAnimation(box, "scale");
                animation->setDuration(250);
                animation->setEasingCurve(QEasingCurve::OutBounce);
                animation->setStartValue(8);
                animation->setEndValue(0.25);
                animation->start(QAbstractAnimation::DeleteWhenStopped);
                connect(animation, SIGNAL(finished()), box, SLOT(deleteLater()));
            }
            rows << y;
        }
    }

    if(rows.count() > 0){
       updateScore(rows.count());
       moveBox();
    }
    box->createBox(QPointF(300,70), obox->getCurShape());
    obox->clearBoxGroup(true);
    obox->createBox(QPointF(500, 70));
}

void myView::moveBox(){
    for(int i = rows.count(); i > 0; --i){
        int row = rows.at(i-1);
        foreach(QGraphicsItem *item, scene()->items(QRectF(199, 49, 202, row-47), Qt::ContainsItemShape)){
            item->moveBy(0, 20);
        }
    }
    rows.clear();

}

void myView::gameOver(){

}

void myView::initView(){

    setRenderHint(QPainter::Antialiasing);

    setCacheMode(CacheBackground);
    setWindowTitle(tr("俄罗斯方块"));
    setWindowIcon(QIcon(":/images/icon.png"));
    setMaximumSize(810, 510);
    setMinimumSize(810, 510);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->setSceneRect(5, 5, 800, 500);
    scene->setBackgroundBrush(QPixmap(":/images/background.png"));
    setScene(scene);

    scoreItem = new QGraphicsTextItem;
    scoreItem->setFont(QFont("Times", 20, QFont::Bold));
    scoreItem->setHtml(tr("score:<font color=red>0</font>"));
    scoreItem->setPos(500,140);
    topLine = scene->addLine(197, 47, 403, 47);
    bottomLine = scene->addLine(197, 453, 403, 453);
    leftLine = scene->addLine(197, 47, 197, 453);
    rightLine = scene->addLine(403, 47, 403, 453);

    box = new BoxGroup();
    obox = new BoxGroup();
    connect(box, SIGNAL(needNextBox()), this, SLOT(clearFullRows()));
    connect(box, SIGNAL(gameOver()), this, SLOT(gameOver()));

    scene->addItem(box);
    scene->addItem(obox);
    scene->addItem(scoreItem);
    startGame();
}

void myView::initGame(){
    box->createBox(QPointF(300, 70));
    box->setFocus();
    box->startTimer(SPEED);
    gameSpeed = SPEED;
    obox->createBox(QPointF(500, 70));
}

void myView::updateScore(const int fullRowNum){
    score+=fullRowNum*10;
    scoreItem->setHtml(tr("score:<font color=red>%1</font>").arg(score));
}
