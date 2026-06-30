#include "handleData.h"
#include "mqtt.h"

// ---------- Network variables ---------- //
#ifdef WIFI_SSID
const char *ssid = STR(WIFI_SSID);
#endif
#ifdef WIFI_PASSWORD
const char *password = STR(WIFI_PASSWORD);
#endif
// ---------- Network variables ---------- //
//TODO: Make system environment variables work to avoid hardcoding credentials
// ---------- MQTT variables ---------- //
// ----- Server side ----- //
#ifdef MQTT_SERVER
// const char *mqtt_server = STR(MQTT_SERVER);
const char *mqtt_server = "test.mosquitto.org";
#endif
#ifdef MQTT_PORT
// const int mqtt_port = atoi(STR(MQTT_PORT));
const int mqtt_port = 1883;
#endif

// ----- Client side ----- //
#ifdef MQTT_USERNAME
const char *mqtt_username = STR(MQTT_USERNAME);
#endif
#ifdef MQTT_PASSWORD
const char *mqtt_password = STR(MQTT_PASSWORD);
#endif
#ifdef DEVICE_NAME
const char *device_name = STR(DEVICE_NAME);
#endif
// ---------- MQTT varaibles ---------- //

Adafruit_ADXL345_Unified adxl345 = Adafruit_ADXL345_Unified(12345);
WiFiClient network;
PicoMQTT::Client mqtt(network,mqtt_server,mqtt_port);
StaticJsonDocument<200> data;

#pragma message("WIFI_SSID from build flags: " WIFI_SSID)
#pragma message("WIFI_PASSWORD from build flags: " WIFI_PASSWORD)
#pragma message("MQTT_SERVER from build flags: " MQTT_SERVER)

void setup(void) 
{
  Serial.begin(9600);
  /* Set and display header for ADXL345 sensor */
  setupSensor(adxl345);
  setupMqtt(mqtt);
}

void loop(void) 
{
  /* Loop sensor values reading */
  sensorLoop(adxl345);
  mqttLoop(mqtt,data,adxl345);
}