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

const double JERK_THRESH_LOW = 3.0;
const double JERK_THRESH_HIGH = 3.0;
const int TIMEFRAME = 20;
const int JOLT_WINDOW_MULTIPLIER = 1;
unsigned long jolt_counter;
const int JOLT_COOLDOWN_MAX = 20;
int jolt_cooldown = 0;
bool check_jerk(double *, double *, double *);

sensors_event_t event;

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
  lis.getEvent(&event);
  curr_x = event.acceleration.x;
  curr_y = event.acceleration.y;
  curr_z = event.acceleration.z;

  // Serial.println("X accel:  "); Serial.print(event.acceleration.x);
  // Serial.print("  \tY accel:  "); Serial.print(event.acceleration.y);
  //Serial.print("  \tZ accel:  "); Serial.print(event.acceleration.z);

  /* Display the results (acceleration is measured in m/s^2) */

  // Serial.print(" \tchange in x: "); Serial.println(change_x);

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

  if (jolt_cooldown-- <= 0) {
    // Only start averaging if we are off the cooldown
    change_y = curr_y-prev_y;
    change_x = curr_x-prev_x;
    change_z = curr_z-prev_z;

    change_x_avg += change_x;
    change_y_avg += change_y;
    change_z_avg += change_z;
    
    if (jolt_counter++ % JOLT_WINDOW_MULTIPLIER == 0) {
      if (check_jerk(&change_x_avg, &change_y_avg, &change_z_avg)) {
        jolt_cooldown = JOLT_COOLDOWN_MAX;
      }
    }
  }

  prev_y = event.acceleration.y;
  prev_x = event.acceleration.x;
  prev_z = event.acceleration.z;


  delay(TIMEFRAME);
}

bool check_jerk(double *x_avg_jerk, double *y_avg_jerk, double *z_avg_jerk) {
  bool fired = false;
  double x_avg = *x_avg_jerk / JOLT_WINDOW_MULTIPLIER;
  double y_avg = *y_avg_jerk / JOLT_WINDOW_MULTIPLIER;
  double z_avg = *z_avg_jerk / JOLT_WINDOW_MULTIPLIER;
  double norm = sqrt(x_avg * x_avg + y_avg * y_avg + z_avg * z_avg);
  if (norm < JERK_THRESH_HIGH && norm < JERK_THRESH_HIGH) {
    //Nothing
    // Serial.print("****x: ");
    // Serial.println(x_avg);
    // Serial.print("****y: ");
    // Serial.println(y_avg);
  // } else {
  //   // Find the orientation and determint the event thusly
  //   Serial.print(event.orientation.x);
  //   Serial.print(", ");
  //   Serial.print(event.orientation.y);
  //   Serial.print(", ");
  //   Serial.println(event.orientation.z);
} else if (event.gyro.x < -3) {
    Serial.println("left-jerk");
    Serial1.println("LEFT");
  } else if (event.gyro.x > 3) {
    Serial.println("right-jerk");
    Serial1.println("RIGHT");
  } else if (event.gyro.y < -3) {
    Serial.println("down-jerk");
    Serial1.println("DOWN");
  } else if (event.gyro.y > 3) {
    Serial.println("up-jerk");
    Serial1.println("UP");
  }
  // } else if (abs(x_avg) > abs(y_avg) && abs(x_avg) > abs(z_avg)) {
  //   if (x_avg >= 0.0) {
  //     Serial.println("jolt right");
  //     Serial1.println("RIGHT");
  //   } else {
  //     Serial.println("jolt left");
  //     Serial1.println("LEFT");
  //   }
  //   Serial.println(x_avg);
  //   Serial.print("--------------");
  //   Serial.println(y_avg);
  //   fired = true;
  // } else if (abs(y_avg) > abs(x_avg) && abs(y_avg) > abs(z_avg)) {
  //   if (y_avg >= 0.0) {
  //     Serial.println("jolt up");
  //     Serial1.println("UP");
  //   } else {
  //     Serial.println("jolt down");
  //     Serial1.println("DOWN");
  //   }
  //   Serial.println(y_avg);
  //   Serial.println("--------------");
  //   fired = true;
  // }

  *x_avg_jerk = 0.0;
  *y_avg_jerk = 0.0;
  *z_avg_jerk = 0.0;
}
