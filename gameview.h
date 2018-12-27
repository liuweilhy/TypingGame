#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QWidget *parent = nullptr);
    GameView(QGraphicsScene *scene, QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);

private:
    bool mouseLeftButtonDown;
    QPoint lastPos;
};

#endif // GAMEVIEW_H
