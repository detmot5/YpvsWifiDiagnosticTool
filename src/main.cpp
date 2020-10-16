//
// Created by Norbert Bielak on 12/10/2020.
//

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SoftwareSerial.h>
#include <MillisTimer.h>


#include "DeviceCommandsService.h"
#include "DeviceCommand.h"
#include "main.h"
#include "httpController.h"
#include "StreamCstringReader.h"
#include "rpmParser.h"
#include "ControlPanel.h"



const char* ssid     = "ESP8266-Access-Point";
const char* password = "123456789";

MillisTimer deviceOkLedTimer = MillisTimer(400, [] (MillisTimer& timer) {
  static bool ledState = false;
  digitalWrite(LED_BUILTIN, ledState);
  digitalWrite(DEVICE_OK_LED_PIN, ledState);
  ledState = !ledState;
});
MillisTimer rpmQueryTimer;
MillisTimer deviceCommandProcessTimer(50, DeviceCommandsService::process);

AsyncWebServer server(80);
SoftwareSerial softSerial(D6, D7);
StreamCStringReader<50> reader(&softSerial, [] (char* string){
  if(strlen(string) > 0){
    createJsonFromRPM(string);
  }
});


void WiFiInit(){
  Serial.print("Setting AP (Access Point)…");
  if(WiFi.softAP(ssid, password)) Serial.println("connected");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  HTTPSetMappings(server);
  server.begin();
}

void millisTimersInit(){
  rpmQueryTimer = MillisTimer(50, [] (MillisTimer& timer){ ypvsRpmQuery(softSerial); });
  rpmQueryTimer.start();
  deviceOkLedTimer.start();
  deviceCommandProcessTimer.start();
}


void setup (){
  Serial.begin(115200);
  softSerial.begin(115200);
  WiFiInit();
  millisTimersInit();

  pinMode(LED_BUILTIN, OUTPUT);
  ControlPanel::init();
  DeviceCommandsService::init(&softSerial);

}



void loop() {
  reader.run();
  deviceOkLedTimer.run();
  rpmQueryTimer.run();
  deviceCommandProcessTimer.run();
  ControlPanel::timer.run();
}