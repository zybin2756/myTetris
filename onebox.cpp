#include "onebox.h"
#include <QPainter>
#include <QPainterPath>

OneBox::OneBox(const QColor &color):brushColor(color){

}

QRectF OneBox::boundingRect() const{
    qreal qpenWidth = 1;
    return QRectF(-10 - qpenWidth/2, -10 - qpenWidth/2,
                  20 + qpenWidth, 20 + qpenWidth);
}
void OneBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(-10, -10, 20, 20, QPixmap(":/images/box.gif"));
    painter->setBrush(brushColor);
    QColor penColor = brushColor;
    penColor.setAlpha(20);
    painter->setPen(penColor);
    painter->drawRect(-10, -10, 20, 20);
}

QPainterPath OneBox::shape() const{
    QPainterPath path;
    path.addRect(-9.5, -9.5, 19, 19);
    return path;
}
