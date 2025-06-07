#include "ocrworker.h"
#include <QtConcurrent>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <QBuffer>

OCRWorker::OCRWorker(QObject *parent)
    : QObject(parent)
{
}

void OCRWorker::enqueue(QString bulletUuid, QImage inkLayer)
{
    QtConcurrent::run(&pool_, [this, bulletUuid, inkLayer]() {
        tesseract::TessBaseAPI api;
        QString text;
        if (api.Init(nullptr, "eng") == 0) {
            QByteArray bytes;
            QBuffer buf(&bytes);
            buf.open(QIODevice::WriteOnly);
            inkLayer.save(&buf, "PNG");
            buf.close();

            Pix *pix = pixReadMem(reinterpret_cast<const unsigned char*>(bytes.constData()), bytes.size());
            if (pix) {
                api.SetImage(pix);
                char *out = api.GetUTF8Text();
                if (out) {
                    text = QString::fromUtf8(out);
                    delete [] out;
                }
                pixDestroy(&pix);
            }
            api.End();
        }
        emit ocrReady(bulletUuid, text.trimmed());
    });
}
