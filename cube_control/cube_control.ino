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
double change_x_avg;
double change_y_avg;
double change_z_avg;

const double JERK_THRESH = 2.0;
const double JERK_THRESH_LOW = 1.0;
const int TIMEFRAME = 25;
const int JOLT_WINDOW_MULTIPLIER = 4;
int jolt_counter;
void check_jerk(double *, double *, double *);

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

   //Serial.print("X ori:  "); Serial.print(event.acceleration.x);
  // Serial.print("  \tY ori:  "); Serial.print(event.acceleration.y);
  // Serial.print("  \tZ ori:  "); Serial.print(event.acceleration.z);

  /* Display the results (acceleration is measured in m/s^2) */

  // Serial.print(" \tchange in x: "); Serial.println(change_x);

  // if(change_y > JERK_THRESH){                      //change in accel y > 10
  //   Serial.println("jolt y up");
  // }
  // else if (change_y < -JERK_THRESH){             //change in accel y < -10
  //      Serial.println("jolt y down");
  //      // Serial1.println("jolt y down");
  //       Serial1.println("DOWN");
  // } else if (change_x < -JERK_THRESH){             //change in accel x < -10
  //     Serial.println("jolt x left");
  //      //Serial1.println("jolt x left");
  //      Serial1.println("LEFT");
  // } else if (change_x > JERK_THRESH){              //change in accel x > 10
  //     Serial.println("jolt x right");
  //    // Serial1.println("jolt x left");
  //     Serial1.println("RIGHT");
  // }
  if (false) {

  }
  else {
      if (event.gyro.y > 8 && event.gyro.y < 9){
      Serial.println("down");
      Serial1.println("W");
    } else if(event.gyro.y < -8 && event.gyro.y > -9){
      Serial.println("up");
      Serial1.println("S");
    } else {
//       Serial.print("Y is at rest");
    }

    if (event.gyro.x > -9 && event.gyro.x < -8){
      Serial.println("left");
      Serial1.println("A");
    } else if  (event.gyro.x < 9 && event.gyro.x > 8){
       Serial.println("right");
       Serial1.println("D");
    } else {
//      Serial.print("X is at rest");
    }
    // Serial.println("");
    // Serial1.println("");
  }
  change_y = curr_y-prev_y;
  change_x = curr_x-prev_x;
  change_z = curr_z-prev_z;

  change_x_avg += change_x;
  change_y_avg += change_y;
  change_z_avg += change_y;

  if (jolt_counter++ % JOLT_WINDOW_MULTIPLIER == 0) {
    check_jerk(&change_x_avg, &change_y_avg, &change_z_avg);
  }

  prev_y = event.acceleration.y;
  prev_x = event.acceleration.x;
  prev_z = event.acceleration.z;


  delay(TIMEFRAME);
}

void check_jerk(double *x_avg_jerk, double *y_avg_jerk, double *z_avg_jerk) {
  double x_avg = *x_avg_jerk / JOLT_WINDOW_MULTIPLIER;
  double y_avg = *y_avg_jerk / JOLT_WINDOW_MULTIPLIER;
  double z_avg = *z_avg_jerk / JOLT_WINDOW_MULTIPLIER;
  // Serial.println(x_avg);
  // Serial.println(y_avg);
  // Serial.println(z_avg);
  if (abs(x_avg) < JERK_THRESH && abs(y_avg) < JERK_THRESH_LOW) {
    //Nothing
  } else if (abs(x_avg) > abs(y_avg) && abs(x_avg) > abs(z_avg)) {
    if (x_avg >= 0.0) {
      Serial.println("jolt right");
      Serial1.println("RIGHT");
    } else {
      Serial.println("jolt left");
      Serial1.println("LEFT");
    }
  } else if (abs(y_avg) > abs(x_avg) && abs(y_avg) > abs(z_avg)) {
    if (y_avg >= 0.0) {
      Serial.println("jolt up");
      Serial1.println("UP");
    } else {
      Serial.println("jolt down");
      Serial1.println("DOWN");
    }
  }

  *x_avg_jerk = 0.0;
  *y_avg_jerk = 0.0;
  *z_avg_jerk = 0.0;
}
