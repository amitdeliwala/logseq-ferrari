import QtQuick 2.15
import QtQuick.Controls 2.15
import Logseq 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1404
    height: 1872

    PenHub { id: penHub }
    OCRWorker { id: ocrWorker }
    Session { id: session }

    Timer {
        interval: 16
        running: true
        repeat: true
        onTriggered: penHub.processBufferedEvents()
    }

    Column {
        id: outline
        anchors.fill: parent
        Repeater {
            model: []
            delegate: Bullet {}
        }
    }

    Connections {
        target: penHub
        function onDoubleTap(pos) {
            var b = outline.childAt(pos.x, pos.y)
            if (b) b.convertLastStroke()
        }
    }
}
