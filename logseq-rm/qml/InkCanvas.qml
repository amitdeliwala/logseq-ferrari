import QtQuick 2.15

Item {
    id: canvas
    signal strokeEnded()

    function toImage() { return null }
    function takeLastStrokeAsImage() { return null }
    function clear() {}
}
