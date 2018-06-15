#include "boxgroup.h"
#include "onebox.h"

#include <QKeyEvent>
#include <QTimer>


BoxGroup::BoxGroup(){
    setFlags(QGraphicsItem::ItemIsFocusable);
    oldTransform = transform();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveOneStep()));
    curShape = RandomShape;
}

QRectF BoxGroup::boundingRect() const{
    qreal penWidth = 1;
    return QRectF(-40 - penWidth/2, -40 - penWidth/2, 80 + penWidth, 80 + penWidth);
}

bool BoxGroup::isColliding(){
    QList<QGraphicsItem *> itemList = childItems();

    QGraphicsItem *item;
    foreach(item, itemList){
        if(item->collidingItems().count() > 1){
            return true;
        }
    }

    return false;
}

void BoxGroup::createBox(const QPointF &point , BoxShape shape){
    static QColor colorList[7] = {QColor(200, 0, 0, 100), QColor(255, 200, 0, 100), QColor(0, 0, 200, 100),
                                  QColor(0, 200, 0, 100), QColor(0, 200, 255, 100), QColor(200, 0, 255, 100),
                                  QColor(150, 100, 100, 100)};
    int shapeid = shape;

    if(shapeid == RandomShape){
//        qsrand(QTime::currentTime().msec());
        shapeid = qrand() % 7;
    }

    QList<OneBox *> list;
    for(int i = 0; i < 4; ++i){
        OneBox *box = new OneBox(colorList[shapeid]);
        list << box;
        addToGroup(box);
    }

    //{ IShape, JShape, LShape, OShape, SShape, ZShape, TShape, RandomShape };
    switch(shapeid){
        case IShape:
            curShape = IShape;
            list.at(0)->setPos(-30, -10);
            list.at(1)->setPos(-10, -10);
            list.at(2)->setPos(10, -10);
            list.at(3)->setPos(30, -10);
        break;
        case JShape:
            curShape = JShape;
            list.at(0)->setPos(10, -10);
            list.at(1)->setPos(10, 10);
            list.at(2)->setPos(10, 30);
            list.at(3)->setPos(-10, 30);
        break;
        case LShape:
            curShape = LShape;
            list.at(0)->setPos(-10, -10);
            list.at(1)->setPos(-10, 10);
            list.at(2)->setPos(-10, 30);
            list.at(3)->setPos(10, 30);
        break;
        case OShape:
            curShape = OShape;
            list.at(0)->setPos(-10, -10);
            list.at(1)->setPos(10, -10);
            list.at(2)->setPos(-10, 10);
            list.at(3)->setPos(10, 10);
        break;
        case SShape:
            curShape = SShape;
            list.at(0)->setPos(10, -10);
            list.at(1)->setPos(30, -10);
            list.at(2)->setPos(-10, 10);
            list.at(3)->setPos(10, 10);
        break;
        case ZShape:
            curShape = ZShape;
            list.at(0)->setPos(-10, -10);
            list.at(1)->setPos(10, -10);
            list.at(2)->setPos(10, 10);
            list.at(3)->setPos(30, 10);
        break;
        case TShape:
            curShape = TShape;
            list.at(0)->setPos(10, -10);
            list.at(1)->setPos(30, -10);
            list.at(2)->setPos(-10, 10);
            list.at(3)->setPos(10, 10);
        break;
        default:
        break;
    }

    setPos(point);
    if(isColliding()){
        stopTimer();
        emit gameOver();
    }
}

void BoxGroup::clearBoxGroup(bool destroyBox){
    QList<QGraphicsItem *> list = childItems();
    QGraphicsItem* item;
    foreach (item, list) {
        removeFromGroup(item);
        if(destroyBox){
            OneBox* box = (OneBox*)item;
            box->deleteLater();
        }
    }
}


//slots
void BoxGroup::moveOneStep(){
    moveBy(0,20);
    if(isColliding()){
        moveBy(0, -20);
        clearBoxGroup();
        emit needNextBox();
    }
}

void BoxGroup::startTimer(int interval){
    timer->start(interval);
}

void BoxGroup::stopTimer(){
    timer->stop();
}


//events
void BoxGroup::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Down:
            moveBy(0,20);
            if(isColliding()){
                moveBy(0, -20);
                clearBoxGroup();
                emit needNextBox();
            }
        break;

        case Qt::Key_Up:
            setRotation(angle + 90);
            if(isColliding()){
                setRotation(angle);
            }else{
                angle = (angle + 90)%360;
            }
        break;

        case Qt::Key_Left:
            moveBy(-20,0);
            if(isColliding()){
                moveBy(20,0);
            }
        break;

        case Qt::Key_Right:
            moveBy(20,0);
            if(isColliding()){
                moveBy(-20,0);
            }
        break;

        case Qt::Key_Space:
            while(!isColliding()){
                moveBy(0,20);
            }
            moveBy(0,-20);
            clearBoxGroup();
            emit needNextBox();
        break;
    }
}
