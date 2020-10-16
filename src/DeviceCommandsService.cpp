//
// Created by norbe on 16/10/2020.
//

#include <Arduino.h>
#include <RingBuffer.h>
#include <MillisTimer.h>
#include "DeviceCommandsService.h"
#include "DeviceCommand.h"

#define COMMANDS_BUFFER_SIZE 100



namespace CMD{
  const char* AT = "AT\n";
  const char* ATI = "ATI\n";
  const char* AT_RPM = "AT+RPM\n";
}






namespace DeviceCommandsService{
  RingBuffer<DeviceCommand, COMMANDS_BUFFER_SIZE> commands;
  Stream* stream;

  void init(Stream* deviceStream){
    stream = deviceStream;
  }

  void send(DeviceCommand& command){
    commands.pushBack(command);
  }

  void process(){
    DeviceCommand commandToSend;
    bool isCommandToSend = commands.getFront(&commandToSend);
    if(isCommandToSend && stream != nullptr){
      stream->print(commandToSend.getCommand());
    }
  }


}



