#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QList>
#include "timer.h"
#include "charitem.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject *parent = nullptr);
    ~GameScene();

public slots:
    void gameStart();
    void gameLevelUp();
    void gameOver();
    void gamePause();
    void addNewCharItem();
    void updateScore();
    void advance();

protected:
    void keyPressEvent(QKeyEvent *keyEvent);

private:
    // 场景默认大小
    QSize size;
    // 分数显示
    QGraphicsSimpleTextItem scoreItem;
    // 关卡显示
    QGraphicsSimpleTextItem levelItem;
    // 提示
    QGraphicsSimpleTextItem tipItem;

    // 字母Item表
    QList<CharItem *> charItemList;

    // 落字母定时器
    Timer timerDown;
    // 刷新界面定时器
    Timer timerUpdate;

    // 游戏标识，0标识未开始，1标识进行中，2表示过关，-1表示游戏已结束
    int flag;
    // 关卡
    uint level;
    // 分数
    int score;
    // 失误数
    uint miss;

    // 关卡落字母数
    int charNum;
    // 当前关卡已出字母数
    int charNumAppeared;
    // 落字母间隔时间(ms)
    int timeDown;
    // 刷新界面的间隔时间(ms)
    int timeUpdate;
    // 落子速度
    qreal itemSpeed;
};

#endif // GAMESCENE_H
