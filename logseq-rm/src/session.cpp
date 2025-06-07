#include "session.h"
#include <QTemporaryFile>
#include <QProcess>
#include <QDir>

Session::Session(QObject *parent)
    : QObject(parent), file_("session.org")
{
}

void Session::setFile(const QString &f)
{
    if (file_ == f)
        return;
    file_ = f;
    emit fileChanged();
}

void Session::embedImage(QString bulletUuid, QImage image)
{
    QTemporaryFile tmp(QDir::temp().filePath(bulletUuid + "_XXXXXX.png"));
    tmp.setAutoRemove(false);
    if (!tmp.open())
        return;
    image.save(&tmp, "PNG");
    tmp.close();

    QString bullet = QString("![[%1]]").arg(tmp.fileName());
    QProcess::execute("logseq-cli", {"embed", "--file", file_, "--bullet", bullet});
}
