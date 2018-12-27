#include "timer.h"

Timer::Timer(QObject *parent) : QTimer(parent), isPause(false), isSingle(false), intervalPrev(0), remainingTimeMsec(0)
{
}

void Timer::start(int msec)
{
    if (!isActive() && isPause) {
        QTimer::start(msec);
    }
    else {
        isPause = false;
        intervalPrev = msec;
        isSingle = isSingleShot();
        QTimer::start(msec);
    }
}

void Timer::start()
{
    if (!isActive() && isPause) {
        isPause = false;
        setSingleShot(isSingle);
        QTimer::start(intervalPrev);
        disconnect(this, SIGNAL(timeout()), this, SLOT(start()));
    }
    else {
        isPause = false;
        QTimer::start(intervalPrev);
    }
}

void Timer::pause()
{
    if (isActive() && !isPause) {
        isPause = true;
        remainingTimeMsec = this->remainingTime();
        connect(this, SIGNAL(timeout()), this, SLOT(start()));
        stop();
    }
}

void Timer::resume()
{
    if (!isActive() && isPause) {
        setSingleShot(true);
        start(remainingTimeMsec);
    }
}
