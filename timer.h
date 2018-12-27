#ifndef TIMER_H
#define TIMER_H
#include <QTimer>

// QTimer派生的Timer类，添加暂停pause和恢复resume功能
// 这个类写得相当不好，勉强能用，所以屏蔽了一些会引起冲突的函数

class Timer : public QTimer
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);

signals:

public slots:
    void start(int msec);
    void start();
    void pause();
    void resume();

    // 以下函数屏蔽
    void start(std::chrono::milliseconds msec) {}
    void setInterval(int msec) {}
    void setInterval(std::chrono::milliseconds value) {}


private:
    bool isPause;
    bool isSingle;
    int intervalPrev;
    int remainingTimeMsec;
};

#endif // TIMER_H
