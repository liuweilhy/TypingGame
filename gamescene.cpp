#include <ctime>
#include "gamescene.h"
#include <QApplication>
#include <QDebug>

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    size(1024,768),
    flag(0),
    level(0),
    score(0),
    miss(0),
    charNum(50),
    charNumAppeared(0),
    timeUpdate(8),
    itemSpeed(3)
{
    setSceneRect(0, 0, size.width(), size.height());

    // 添加得分显示
    scoreItem.setFont(QFont("Arial", 16, QFont::Normal));
    scoreItem.setBrush(QBrush(Qt::gray));
    scoreItem.setPos(10,8);
    scoreItem.setZValue(1);
    addItem(&scoreItem);
    updateScore();

    // 添加提示
    tipItem.setFont(QFont("Arial", 10, QFont::Light, true));
    tipItem.setBrush(QBrush(Qt::gray));
    tipItem.setZValue(1);
    addItem(&tipItem);

    // 添加关卡显示
    levelItem.setFont(QFont("Arial", 36, QFont::Bold));
    levelItem.setBrush(QBrush(Qt::gray));
    levelItem.setZValue(1);
    addItem(&levelItem);

    // 关联定时器与落字母
    connect(&timerDown, SIGNAL(timeout()), this, SLOT(addNewCharItem()));

    // scene的advance来使子部件动起来
    connect(&timerUpdate, SIGNAL(timeout()), this, SLOT(advance()));

    // 初始化随机数
    srand(time(0));

    // 启动
    gameLevelUp();
}

GameScene::~GameScene()
{
}

void GameScene::gameStart()
{
    if (flag == 1) {
        timerDown.resume();
        timerUpdate.resume();
        return;
    }

    if (flag == 0 || flag == -1) {
        flag = 1;
        level = 1;
        score = 0;
        miss = 0;
        itemSpeed = 3;

        charNum = 60;
        charNumAppeared = 0;
        timeDown = 60000 / (40+20*level);
        itemSpeed = 3 * timeDown;

        qDeleteAll(charItemList);
        charItemList.clear();
    }
    else if (flag == 2) {
        flag = 1;
        qDeleteAll(charItemList);
        charItemList.clear();
    }

    timerDown.start(timeDown);
    timerUpdate.start(timeUpdate);

    levelItem.hide();

    updateScore();

    tipItem.setText("Press Space to pause or resume. Press ESC to quit.");
    tipItem.setPos(10, size.height() - tipItem.boundingRect().height() * 1.25);
    tipItem.show();
}

void GameScene::gameLevelUp()
{
    if (flag != 0 && flag != 1)
        return;

    timerDown.stop();
    timerUpdate.stop();

    flag = 2;
    // 升级，提高难度
    level++;
    // 每关落字母数，1级60个，2级80个，3级100个，以此类推
    charNum = 40 + 20 * level;
    charNumAppeared = 0;
    // 落字母时间间隔
    timeDown = 60000 / charNum;
    // 落下速度
    itemSpeed = 3 * timeDown;

    levelItem.setText(QString("Level  %1").arg(level));
    levelItem.setPos((size.width() - levelItem.boundingRect().width())*0.5,
                     (size.height() - levelItem.boundingRect().height())*0.5);
    levelItem.show();

    tipItem.setText("Press ENTER to start, or ESC to quit.");
    tipItem.setPos(levelItem.x() + (levelItem.boundingRect().width() - tipItem.boundingRect().width()) * 0.5,
                   levelItem.y() + levelItem.boundingRect().height() + tipItem.boundingRect().height() * 0.25);
    tipItem.show();
}

void GameScene::gameOver()
{
    timerDown.stop();
    timerUpdate.stop();

    flag = -1;

    levelItem.setText(QString("Game Over!  Your score: %1").arg(score));
    levelItem.setPos((size.width() - levelItem.boundingRect().width())*0.5,
                     (size.height() - levelItem.boundingRect().height())*0.5);
    levelItem.show();

    tipItem.setText("Press ENTER to restart, or ESC to quit.");
    tipItem.setPos(levelItem.x() + (levelItem.boundingRect().width() - tipItem.boundingRect().width()) * 0.5,
                   levelItem.y() + levelItem.boundingRect().height() + tipItem.boundingRect().height() * 0.25);
    tipItem.show();
}

void GameScene::gamePause()
{
    timerDown.pause();
    timerUpdate.pause();
}

void GameScene::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        gameStart();
        break;

    case Qt::Key_Space:
        if (flag != 1)
            break;
        if (timerUpdate.isActive())
            gamePause();
        else
            gameStart();
        break;

    case Qt::Key_Escape:
        QApplication *app;
        app->quit();
        break;

    default:
        if (timerUpdate.isActive()) {
            auto i = charItemList.begin();
            while (i != charItemList.end()) {
                if (keyEvent->key() == (*i)->getKey()) {
                    delete *i;
                    charItemList.erase(i);
                    score++;
                    updateScore();
                    keyEvent->accept();
                    return;
                }
                else
                    i++;
            }
        }
    }
}

void GameScene::addNewCharItem()
{
    if (charNumAppeared >= charNum)
        timerDown.stop();
    else {
        CharItem *item = new CharItem;
        int x = rand() % (size.width() - item->getSize()) + item->getSize() / 2;
        item->setPos(x, 0);
        charItemList.append(item);
        addItem(item);
        charNumAppeared++;
    }
}

void GameScene::updateScore()
{
    scoreItem.setText(QString("level : %1   score: %2    miss: %3").arg(level).arg(score).arg(miss));
}

void GameScene::advance()
{
    QGraphicsScene::advance();
    auto i = charItemList.begin();
    while (i != charItemList.end()) {
        if ((*i)->pos().ry() >= height()) {
            delete *i;
            charItemList.erase(i++);
            miss++;
            updateScore();
        }
        else
            i++;
    }

    if (miss >= 10) {
        gameOver();
        return;
    }

    // 过关
    if (!timerDown.isActive() && charItemList.isEmpty()) {
        gameLevelUp();
    }
}
