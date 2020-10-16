//
// Created by norbe on 14/10/2020.
//


#include <Arduino.h>
#include <MillisTimer.h>

#include "ControlPanel.h"
#include "main.h"

namespace ControlPanel {


  void task(MillisTimer& tim){
    digitalWrite(SERIAL_RECEIVED_LED_PIN, LOW);
    digitalWrite(HTTP_REQUEST_LED_PIN, LOW);
    digitalWrite(ERROR_LED_PIN, LOW);
  }


  MillisTimer timer(100, task); // turn off communication leds every 50000ms


  void init(){
    pinMode(SERIAL_RECEIVED_LED_PIN, OUTPUT);
    pinMode(HTTP_REQUEST_LED_PIN, OUTPUT);
    pinMode(DEVICE_OK_LED_PIN, OUTPUT);
    pinMode(ERROR_LED_PIN, OUTPUT);
    timer.start();
  }




};



