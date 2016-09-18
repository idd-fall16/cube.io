/* Graph I2C Accelerometer On RedBear Duo over Serial Port
 * Adafruit Part 2809 LIS3DH - http://adafru.it/2809
 * This example shows how to program I2C manually
 * I2C Pins SDA1==D0, SCL1 == D1
 * Default address: 0x18
 */
 
// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif
// Basic demo for accelerometer readings from Adafruit LIS3DH

#include "Adafruit_LIS3DH.h"
#include "Adafruit_Sensor.h"

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

double prev_x;
double prev_y;
double prev_z;
double curr_x;
double curr_y;
double curr_z;
//double prev_x;
//double prev_z;
double change_x;
double change_y;
double change_z;
//int dir = 0;





void setup(void) {
  
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(D17, INPUT);
  pinMode(D16, INPUT);
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  //Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  //Serial.println("G");
}

void loop() {
  
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
//  Serial.print("X:  "); Serial.print(lis.x); 
//  Serial.print("  \tY:  "); Serial.print(lis.y); 
//  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  curr_x = event.acceleration.x;
  curr_y = event.acceleration.y;
  curr_z = event.acceleration.z;

  Serial.print("X:  "); Serial.print(event.orientation.x); 
  Serial.print("  \tY:  "); Serial.print(event.orientation.y); 
  Serial.print("  \tZ:  "); Serial.print(event.orientation.z); 
  
  /* Display the results (acceleration is measured in m/s^2) */

  Serial.print(" \tchange in x: "); Serial.println(change_x); 
  
  if(change_y > 5){                      //change in accel y > 10
    Serial.println("jolt y up");
  }
  else if (change_y < -5){             //change in accel y < -10
       Serial.println("jolt y down");
       // Serial1.println("jolt y down");
        Serial1.println("DOWN");
  } else if (change_x < -5){             //change in accel x < -10
      Serial.println("jolt x left");
       //Serial1.println("jolt x left");
       Serial1.println("LEFT");
  } else if (change_x > 5){              //change in accel x > 10
      Serial.println("jolt x right");
     // Serial1.println("jolt x left");
      Serial1.println("RIGHT");
  } else {
      if (event.gyro.y > 4 && event.gyro.y < 10){
      Serial.print("up");
      Serial1.print("W");
    } else if(event.gyro.y < -4 && event.gyro.y > -10){
      Serial.print("down");
      Serial1.print("S");
    } else {
//       Serial.print("Y is at rest");
    }
    
    if (event.gyro.x > -10 && event.gyro.x < -4){
      Serial.print("left");
      Serial1.print("A");
    } else if  (event.gyro.x < 10 && event.gyro.x > 4){
       Serial.print("right");
       Serial1.print("D");
    } else {
//      Serial.print("X is at rest");
    }
    Serial.println("");
    Serial1.println("");
  }
  change_y = curr_y-prev_y;
  change_x = curr_x-prev_x;
  change_z = curr_z-prev_z;
  prev_y = event.acceleration.y;
  prev_x = event.acceleration.x;
  prev_z = event.acceleration.z;
  
  delay(100); 
}


