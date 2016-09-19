var SerialPort = require("serialport");
var Robot = require("robotjs");
var ChildProcess = require("child_process");

const GAME_URL = 'http://g-kak.com/kyubi/';

var port = new SerialPort('/dev/tty.HC-06-DevB', {
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
    if (key === 'q') {
      Robot.typeString('q');
    }
    /* Turns */
    else if (key === 'W') {
      Robot.typeString('W');
    }
    else if (key === 'A') {
      Robot.typeString('A');
    }
    else if (key === 'S') {
      Robot.typeString('S');
    }
    else if (key === 'D') {
      Robot.typeString('D');
    }
    /* Cube movements */
    else if (key === 'UP') {
      Robot.keyTap('up');
    }
    else if (key === 'DOWN') {
      Robot.keyTap('down');
    }
    else if (key === 'LEFT') {
      Robot.keyTap('left');
    }
    else if (key === 'RIGHT') {
      Robot.keyTap('right');
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
