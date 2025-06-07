#ifndef PENHUB_H
#define PENHUB_H

#include <QObject>
#include <QHash>
#include <QPointF>
#include <QElapsedTimer>

class PenHub : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool strokeActive READ strokeActive NOTIFY strokeActiveChanged)
public:
    explicit PenHub(QObject *parent=nullptr);

    bool strokeActive() const { return !active_.isEmpty(); }

    void processBufferedEvents();

signals:
    void strokeStarted(int id, QPointF pos, float pressure);
    void strokePoint(int id, QPointF pos, float pressure);
    void strokeEnded(int id);
    void doubleTap(QPointF pos);
    void strokeActiveChanged();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    struct Stroke {
        QVector<QPointF> pts;
        QVector<float>    pressures;
        QElapsedTimer     timer;
    };
    QHash<int, Stroke> active_;
    QPointF lastReleasePos_;
    qint64  lastReleaseTimeMs_{0};
};

#endif // PENHUB_H
