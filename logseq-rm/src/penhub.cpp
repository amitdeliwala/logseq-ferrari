#include "penhub.h"
#include <QEvent>
#include <QTabletEvent>
#include <QCoreApplication>

PenHub::PenHub(QObject *parent)
    : QObject(parent)
{
    qApp->installEventFilter(this);
}

void PenHub::processBufferedEvents()
{
    // Placeholder for low-latency processing
}

bool PenHub::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type()) {
    case QEvent::TabletPress: {
        auto *ev = static_cast<QTabletEvent*>(event);
        Stroke s; s.timer.start();
        active_.insert(ev->pointerId(), s);
        emit strokeStarted(ev->pointerId(), ev->posF(), ev->pressure());
        break;
    }
    case QEvent::TabletMove: {
        auto *ev = static_cast<QTabletEvent*>(event);
        auto it = active_.find(ev->pointerId());
        if (it != active_.end()) {
            it->pts.append(ev->posF());
            emit strokePoint(ev->pointerId(), ev->posF(), ev->pressure());
        }
        break;
    }
    case QEvent::TabletRelease: {
        auto *ev = static_cast<QTabletEvent*>(event);
        active_.remove(ev->pointerId());
        emit strokeEnded(ev->pointerId());
        emit strokeActiveChanged();
        lastReleasePos_ = ev->posF();
        lastReleaseTimeMs_ = ev->timestamp();
        break;
    }
    default:
        break;
    }
    return QObject::eventFilter(obj, event);
}
