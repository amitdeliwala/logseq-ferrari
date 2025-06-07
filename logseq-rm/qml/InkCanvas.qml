import QtQuick 2.15

Item {
    id: canvas
    signal strokeEnded()

    property var strokes: []
    property var current: []

    Canvas {
        id: c
        anchors.fill: parent
        renderTarget: Canvas.Image
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0,0,width,height);
            ctx.lineWidth = 2;
            ctx.lineCap = "round";
            ctx.lineJoin = "round";
            ctx.strokeStyle = "black";
            function drawStroke(arr){
                if (arr.length === 0) return;
                ctx.beginPath();
                ctx.moveTo(arr[0].x, arr[0].y);
                for (var i=1;i<arr.length;i++) ctx.lineTo(arr[i].x, arr[i].y);
                ctx.stroke();
            }
            for (var i=0;i<strokes.length;i++)
                drawStroke(strokes[i]);
            drawStroke(current);
        }
    }

    Connections {
        target: penHub
        onStrokeStarted: { current = [{x:pos.x, y:pos.y}]; c.requestPaint(); }
        onStrokePoint: { if (current) { current.push({x:pos.x, y:pos.y}); c.requestPaint(); } }
        onStrokeEnded: {
            if (current) strokes.push(current);
            current = [];
            c.requestPaint();
            canvas.strokeEnded();
        }
    }

    function toImage() {
        return c.image
    }
    function takeLastStrokeAsImage() {
        if (strokes.length === 0) return null
        var s = strokes[strokes.length-1]
        if (s.length === 0) return null
        var minX=s[0].x, minY=s[0].y, maxX=s[0].x, maxY=s[0].y
        for (var i=1;i<s.length;i++) {
            var p = s[i]
            minX = Math.min(minX, p.x)
            minY = Math.min(minY, p.y)
            maxX = Math.max(maxX, p.x)
            maxY = Math.max(maxY, p.y)
        }
        return c.image.copy(minX, minY, maxX-minX+1, maxY-minY+1)
    }
    function clear() {
        strokes = []
        current = []
        c.requestPaint()
    }
}
