#ifndef CHARITEM_H
#define CHARITEM_H

#include <QGraphicsItem>

class CharItem : public QGraphicsItem
{
public:
    CharItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    void setSpeed(qreal speed) { this->speed = speed; }
    int getKey() const { return key; }
    int getSize() const { return size; }

protected:
    void advance(int step) override;

private:
    int key;
    int size;
    qreal speed;
    QColor colorChar;
    QColor colorBackground;
    QColor colorFrame;
};

#endif
