#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QImage>

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString file READ file WRITE setFile NOTIFY fileChanged)
public:
    explicit Session(QObject *parent = nullptr);

    QString file() const { return file_; }
    void setFile(const QString &f);

public slots:
    void embedImage(QString bulletUuid, QImage image);

signals:
    void fileChanged();

private:
    QString file_;
};

#endif // SESSION_H
