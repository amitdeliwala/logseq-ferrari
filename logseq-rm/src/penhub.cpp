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
    for (auto it = active_.begin(); it != active_.end(); ++it) {
        auto &s = it.value();
        while (!s.pts.isEmpty()) {
            QPointF p = s.pts.takeFirst();
            float pressure = s.pressures.isEmpty() ? 1.f : s.pressures.takeFirst();
            emit strokePoint(it.key(), p, pressure);
        }
    }
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
            it->pressures.append(ev->pressure());
        }
        break;
    }
    case QEvent::TabletRelease: {
        auto *ev = static_cast<QTabletEvent*>(event);
        auto it = active_.find(ev->pointerId());
        if (it != active_.end()) {
            it->pts.append(ev->posF());
            it->pressures.append(ev->pressure());
        }
        active_.remove(ev->pointerId());
        emit strokeEnded(ev->pointerId());
        emit strokeActiveChanged();
        if (ev->timestamp() - lastReleaseTimeMs_ < 300 &&
            (ev->posF() - lastReleasePos_).manhattanLength() < 20) {
            emit doubleTap(ev->posF());
            lastReleaseTimeMs_ = 0;
        } else {
            lastReleasePos_ = ev->posF();
            lastReleaseTimeMs_ = ev->timestamp();
        }
        break;
    }
    default:
        break;
    }
    return QObject::eventFilter(obj, event);
}
