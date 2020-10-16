//
// Created by norbe on 16/10/2020.
//

#ifndef WIFIDEBUGGER_DEVICECOMMAND_H
#define WIFIDEBUGGER_DEVICECOMMAND_H

enum class CommandMode{AT_PARAM, AT_NOPARAM, AT_ASK};


class DeviceCommand{
public:

  DeviceCommand(const char* commandStr, CommandMode mode, int param = 0);
  DeviceCommand();
  String getCommand() const;

  void setParam(int param);
  int getParam() const;

  void setMode(CommandMode commandMode);
  CommandMode getMode() const;



private:
  String getNoParamCommand() const;
  String getParamCommand() const;
  String getAskCommand() const ;
  int param;
  CommandMode mode;
  const char* commandStr;
};



#endif //WIFIDEBUGGER_DEVICECOMMAND_H
