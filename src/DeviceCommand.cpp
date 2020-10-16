//
// Created by norbe on 16/10/2020.
//


#include <Arduino.h>
#include "DeviceCommand.h"



DeviceCommand::DeviceCommand(const char* commandStr, CommandMode mode, int param){
  this->commandStr = commandStr;
  this->mode = mode;
  this->param = param;
}
DeviceCommand::DeviceCommand(){
  this->commandStr = "";
  this->mode = CommandMode::AT_NOPARAM;
  this->param =0;
}

String DeviceCommand::getCommand() const {
  switch (this->mode) {
    case CommandMode::AT_PARAM:
      return getParamCommand();
    case CommandMode::AT_ASK:
      return getAskCommand();
    default:
      return getNoParamCommand();
  }
}

void DeviceCommand::setParam(int param){
  this->param = param;
}

int DeviceCommand::getParam() const {
  return this->param;
}

void DeviceCommand::setMode(CommandMode commandMode){
  this->mode = commandMode;
}

CommandMode DeviceCommand::getMode() const {
  return this->mode;
}

String DeviceCommand::getParamCommand() const {
  String command;
  command.reserve(20);
  command += this->commandStr;
  command += "=";
  command += this->param;
  command += "\n";
  return command;
}

String DeviceCommand::getNoParamCommand() const{
  String command;
  command.reserve(10);
  command += this->commandStr;
  command += "\n";
  return command;
}

String DeviceCommand::getAskCommand() const {
  String command;
  command += this->commandStr;
  command += "?\n";
  return command;
}








