#include "handleData.h"

void setup(void) 
{
  Serial.begin(115200);
  /* Set and display header for ADXL345 sensor */
  setupSensor(adxl345);
}

void loop(void) 
{
  /* Loop sensor values reading */
  sensorLoop(adxl345);
}