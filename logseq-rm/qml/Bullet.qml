import QtQuick 2.15
import Logseq 1.0

Item {
    id: bullet
    property string uuid
    property int depth: 0
    property string content: ""

    Row {
        spacing: 8
        Text { text: "\u2022".repeat(depth+1); font.pixelSize: 40 }
        Text { id: mdText; text: content; visible: content.length > 0 }
        InkCanvas {
            id: ink
            anchors.fill: parent
            visible: content.length === 0
            onStrokeEnded: {
                var img = ink.takeLastStrokeAsImage()
                session.embedImage(uuid, img)
            }
        }
    }

    function convertLastStroke() {
        var image = ink.takeLastStrokeAsImage()
        ocrWorker.enqueue(uuid, image)
    }

    Connections {
        target: ocrWorker
        function onOcrReady(bId, text) {
            if (bId !== uuid) return
            content = text
            mdText.text = text
            mdText.visible = true
            ink.clear()
        }
    }
}
