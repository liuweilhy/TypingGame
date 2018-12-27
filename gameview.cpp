#include <QGraphicsScene>
#include <QMouseEvent>
#include "gameview.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent),
    mouseLeftButtonDown(false)
{
    setObjectName("view");
    setRenderHint(QPainter::Antialiasing);
    setStyleSheet("QGraphicsView#view{border-image:url(:/images/background.jpg)}" );
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setFixedSize(scene()->width(), scene()->height());
    // 无窗口模式
    setWindowFlags(Qt::FramelessWindowHint);
}

GameView::GameView(QGraphicsScene *scene, QWidget *parent):
    QGraphicsView(scene, parent)
{
    setObjectName("view");
    setRenderHint(QPainter::Antialiasing);
    setStyleSheet("QGraphicsView#view{border-image:url(:/images/background.jpg)}" );
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setFixedSize(scene->width(), scene->height());
    // 无窗口模式
    setWindowFlags(Qt::FramelessWindowHint);
}

void GameView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseLeftButtonDown) {
        move(x() + (mouseEvent->globalX() - lastPos.x()),
             y() + (mouseEvent->globalY() - lastPos.y()));
        lastPos = mouseEvent->globalPos();
    }
}

void GameView::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        mouseLeftButtonDown = true;
        lastPos = mouseEvent->globalPos();
    }
}

void GameView::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
        mouseLeftButtonDown = false;
}
