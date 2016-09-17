# cube.io
Cube-based game controller for Interactive Device Design.

Designed for the game [Kyubi](http://g-kak.com/kyubi/).

### Quick Start
1. Open the `cube_control.ino` and push the sketch to your microcontroller.
2. Navigate to the `serial_to_key` directory. Make sure you have ``npm`` installed, and run `$ npm install` .
3. Make sure you have a connection to the microcontroller over a serial port. Then run `$ node serial_to_key.js` to begin listening for serial input from the microcontroller.
4. Open a web browser and navigate to the [Kyubi Game](http://g-kak.com/kyubi/). Have fun playing! Controls are as follows:

| cube.io Control| Action        | Native Key  |
| -------------  | ------------- | ----------- |
| Jolt Left | Move black square left | Left
| Jolt Right | Move black square right | Right
| Jolt Up | Move black square up | Up
| Jolt Down | Move black square down | Down
| Turn Forward | Change perspective forward | W
| Turn Backward | Change perspective backward | S
| Turn Leftways | Change perspective left | A
| Turn Rightways | Change perspective right | D


### Software Implementation
To do...

### Hardware Implementation
To do...