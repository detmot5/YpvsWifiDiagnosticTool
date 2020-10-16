//
// Created by norbe on 12/10/2020.
//

#include <Arduino.h>
#include "rpmParser.h"
#include "main.h"

char jsonBuffer[100];


void ypvsRpmQuery(SoftwareSerial& serial){
    const char* message = "AT+RPM?\n";
    serial.print(message);
    Serial.print(message);
}

void createJsonFromRPM(char* string){
  digitalWrite(SERIAL_RECEIVED_LED_PIN, HIGH);
  if(strstr(string, "AT_RPM")) {
    char* value;
    strtok_r(string, "=", &value);
    sprintf(jsonBuffer, R"({"rpm" : "%s"})", value);
  } else if(strstr(string, "OK")) {
    Serial.println("OK");
  } else {
    digitalWrite(ERROR_LED_PIN, HIGH);
    Serial.println("Error");
  }
}

char* getRPMInJSON(){
  return jsonBuffer;
}



