#ifndef OCRWORKER_H
#define OCRWORKER_H

#include <QObject>
#include <QThreadPool>
#include <QImage>

class OCRWorker : public QObject
{
    Q_OBJECT
public:
    explicit OCRWorker(QObject *parent=nullptr);

public slots:
    void enqueue(QString bulletUuid, QImage inkLayer);

signals:
    void ocrReady(QString bulletUuid, QString text);

private:
    QThreadPool pool_;
};

#endif // OCRWORKER_H
