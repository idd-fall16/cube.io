var SerialPort = require("serialport");
var Robot = require("robotjs");
var ChildProcess = require("child_process");

const GAME_URL = 'http://g-kak.com/kyubi/';
const BLE_PORT = '/dev/tty.HC-06-DevB';
const WIRE_PORT = '/dev/tty.usbmodem1411';

var port = new SerialPort(BLE_PORT, {
    baudRate: 9600,
    //parser: SerialPort.parsers.newLine
});

port.on('open', function() {
    console.log('Serial connection open. Opening Chrome and going to website...');
    ChildProcess.exec('open -a "Google Chrome" ' + GAME_URL, function(error, stdout, stderr) {
      if (error) {
        console.error(error);
      } else {
        console.log('... Done.');
      }
    });
});

port.on('data', function(data) {
    var key = data.toString().trim();
    console.log('Got: ' + key);
    if (key === 'q') {
      Robot.typeString('q');
    }
    /* Turns */
    else if (key === 'W') {
      Robot.typeString('W');
      console.log('W');
    }
    else if (key === 'A') {
      Robot.typeString('A');
      console.log('A');
    }
    else if (key === 'S') {
      Robot.typeString('S');
      console.log('S');
    }
    else if (key === 'D') {
      Robot.typeString('D');
      console.log('D');
    }
    /* Cube movements */
    else if (key === 'I') {
      Robot.keyTap('up');
      console.log('up');
    }
    else if (key === 'K') {
      Robot.keyTap('down');
      console.log('down');
    }
    else if (key === 'J') {
      Robot.keyTap('left');
      console.log('left');
    }
    else if (key === 'L') {
      Robot.keyTap('right');
      console.log('right');
    }

});

function doSine() {
    //Speed up the mouse.
    Robot.setMouseDelay(2);

    var twoPI = Math.PI * 2.0;
    var screenSize = Robot.getScreenSize();
    var height = (screenSize.height / 2) - 10;
    var width = screenSize.width;

    for (var x = 0; x < width; x++)
    {
        y = height * Math.sin((twoPI * x) / width) + height;
        Robot.moveMouse(x, y);
    }
}
