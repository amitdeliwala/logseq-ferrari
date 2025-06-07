#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "penhub.h"
#include "ocrworker.h"
#include "session.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<PenHub>("Logseq", 1, 0, "PenHub");
    qmlRegisterType<OCRWorker>("Logseq", 1, 0, "OCRWorker");
    qmlRegisterType<Session>("Logseq", 1, 0, "Session");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/App.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
