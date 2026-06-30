/**
 * @file mqtt.cpp
 * @brief Connect to MQTT broker and publish Sensor data
 * 
 * @copyright
 * This code is partly taken from:
 *  - https://github.com/amusarra/esp32-mqtt-publish-subscribe
 *  - https://esp32io.com/tutorials/esp32-mqtt
 *  - https://github.com/mlesniew/PicoMQTT
 */

#include "mqtt.h"
#include "handleData.h"

void setupMqtt(PicoMQTT::Client& mqtt){
    WiFi.mode(WIFI_STA);
    Serial.println("Trying to connect to: "); 
    Serial.println(ssid);
    WiFi.begin(ssid,password);
    Serial.println("\nConnecting to WiFi Network ...");

    // Block until connected, otherwise no point in doing mqtt
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    mqtt.connected_callback = [] {
        Serial.println("MQTT connected");
    };

    mqtt.disconnected_callback = [] {
        Serial.println("MQTT disconnected");
    };

    mqtt.begin();
    Serial.println("MQTT session start");
}

// Format sensor data in json and publish
void publishData(PicoMQTT::Client& mqtt,StaticJsonDocument<200>& json,Adafruit_ADXL345_Unified& adxl345){

    /* Retrieve real physical value*/
    sensors_event_t event;
    adxl345.getEvent(&event);

    /* Put data in json to be published, significative digits set at 3, change it if needed */
    json[topic_adxl345_X] = round_sig(event.acceleration.x,3);
    json[topic_adxl345_Y] = round_sig(event.acceleration.y,3);
    json[topic_adxl345_Z] = round_sig(event.acceleration.z,3);
    
    /* publish using begin_publish()/send() API */ 
    auto publish = mqtt.begin_publish("test/esp32/adxl345/", measureJson(json));
    serializeJson(json, publish);
    publish.send();
} 

void mqttLoop(PicoMQTT::Client& mqtt,StaticJsonDocument<200>& json,Adafruit_ADXL345_Unified& adxl345){
    mqtt.loop();
    publishData(mqtt,json,adxl345);
}