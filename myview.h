#ifndef MYVIEW_H
#define MYVIEW_H

#include "boxgroup.h"

#include <QGraphicsView>

class myView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myView(QWidget *parent = nullptr);

public slots:
    void startGame();
    void clearFullRows();
    void moveBox();
    void gameOver();

private:
    BoxGroup *box;
    BoxGroup *obox;

    QGraphicsTextItem *scoreItem;

    QGraphicsLineItem *topLine;
    QGraphicsLineItem *bottomLine;
    QGraphicsLineItem *leftLine;
    QGraphicsLineItem *rightLine;

    int score = 0;
    qreal gameSpeed;
    QList<int> rows;
    void initView();
    void initGame();
    void updateScore(const int fullRowNum = 0);
};

#endif // MYVIEW_H
