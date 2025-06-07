#include "ocrworker.h"
#include <QtConcurrent>

OCRWorker::OCRWorker(QObject *parent)
    : QObject(parent)
{
}

void OCRWorker::enqueue(QString bulletUuid, QImage inkLayer)
{
    QtConcurrent::run(&pool_, [this, bulletUuid, inkLayer]() {
        // Placeholder for Tesseract OCR
        QString text = ""; // TODO: integrate Tesseract
        emit ocrReady(bulletUuid, text.trimmed());
    });
}
