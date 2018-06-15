#ifndef BOXGROUP_H
#define BOXGROUP_H

#include <QObject>
#include <QGraphicsItemGroup>

class BoxGroup : public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:
    enum BoxShape { IShape, JShape, LShape, OShape, SShape, ZShape, TShape, RandomShape };
    BoxGroup();
    QRectF boundingRect() const;
    bool isColliding();
    void createBox(const QPointF &point = QPointF(0,0), BoxShape = RandomShape);
    void clearBoxGroup(bool destroyBox = false);
    BoxShape getCurShape(){
        return curShape;
    }
protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void needNextBox();
    void gameOver();

public slots:
    void moveOneStep();
    void startTimer(int interval);
    void stopTimer();

private:
    BoxShape curShape;
    QTransform oldTransform;
    QTimer *timer;
    int angle = 0;
};

#endif // BOXGROUP_H
