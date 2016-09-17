var SerialPort = require("serialport");
var robot = require("robotjs");

var port = new SerialPort('/dev/tty.usbmodem1421', {
    baudRate: 9600,
    //parser: SerialPort.parsers.newLine
});

port.on('open', function() {
    console.log('Serial connection open.');
});

port.on('data', function(data) {
    var key = data.toString().trim();
    if (key === 'q') {
      robot.typeString('q');
    }
});

function doSine() {
    //Speed up the mouse.
    robot.setMouseDelay(2);

    var twoPI = Math.PI * 2.0;
    var screenSize = robot.getScreenSize();
    var height = (screenSize.height / 2) - 10;
    var width = screenSize.width;

    for (var x = 0; x < width; x++)
    {
        y = height * Math.sin((twoPI * x) / width) + height;
        robot.moveMouse(x, y);
    }
}
