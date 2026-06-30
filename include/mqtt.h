#include <cstdlib>
#include <WiFi.h>
#include <PicoMQTT.h>
#include <ArduinoJson.h>
#include <ArduinoLog.h>
#include <Adafruit_ADXL345_U.h>

// Macro to read build flags
#define ST(A) #A
#define STR(A) ST(A)

// ---------- Network variables ---------- //
#ifdef WIFI_SSID
extern const char *ssid;
#endif
#ifdef WIFI_PASSWORD
extern const char *password;
#endif
// ---------- Network variables ---------- //


// ---------- MQTT variables ---------- //
// ----- Server side ----- //
#ifdef MQTT_SERVER
extern const char *mqtt_server;
#endif
#ifdef MQTT_PORT
extern const int mqtt_port;
#endif

// ----- Client side ----- //
#ifdef MQTT_USERNAME
extern const char *mqtt_username;
#endif
#ifdef MQTT_PASSWORD
extern const char *mqtt_password;
#endif
#ifdef DEVICE_NAME
extern const char *device_name;
#endif

// ----- Publish variables ----- //
#define topic_adxl345_X "X"
#define topic_adxl345_Y "Y"
#define topic_adxl345_Z "Z"
#define PUBLISH_INTERVAL 5000;  //5 sec
// ---------- MQTT varaibles ---------- //

/* Variables */
extern WiFiClient network;
extern PicoMQTT::Client mqtt;
extern StaticJsonDocument<200> data;

/* Prototypes */
void setupMqtt(PicoMQTT::Client& mqtt);
void publishData(PicoMQTT::Client& mqtt,StaticJsonDocument<200>& json,Adafruit_ADXL345_Unified& adxl345);
void mqttLoop(PicoMQTT::Client& mqtt,StaticJsonDocument<200>& json,Adafruit_ADXL345_Unified& adxl345);