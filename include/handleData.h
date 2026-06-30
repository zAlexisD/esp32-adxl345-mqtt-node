#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Variable */
extern Adafruit_ADXL345_Unified adxl345;

/* Setup and Test functions prototype*/
void displaySensorDetails(Adafruit_ADXL345_Unified& accel);
void displayDataRate(Adafruit_ADXL345_Unified& accel);
void displayRange(Adafruit_ADXL345_Unified& accel);
void setupSensor(Adafruit_ADXL345_Unified& accel);
void sensorLoop(Adafruit_ADXL345_Unified& accel);

/* Data handling prototypes */
float round_sig(float x, int n);