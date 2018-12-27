#include "charitem.h"

#include <QGraphicsScene>
#include <QPainter>
#include <ctime>

CharItem::CharItem(QGraphicsItem *parent ) :
    QGraphicsItem(parent),
    speed(2.8),
    size(48),
    colorBackground(Qt::yellow),
    colorChar(Qt::darkGray),
    colorFrame(Qt::black)
{
    key = rand() % 26 + 0x41;
}

QRectF CharItem::boundingRect() const
{
    return QRectF(-size/2, -size/2, size, size);
}

QPainterPath CharItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void CharItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Frame
    painter->setBrush(colorFrame);
    painter->drawRoundedRect(boundingRect(), size*0.125, size*0.125);

    // Background
    painter->setBrush(colorBackground);
    painter->drawRoundedRect(-size*0.475, -size*0.475, size*0.95, size*0.95, size*0.118, size*0.118);

    // Text
    QFont font("Arial", size*0.56);
    painter->setBrush(colorChar);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, QChar(key));
}

void CharItem::advance(int step)
{
    if (!step)
        return;

    setPos(mapToParent(0, speed));
}
