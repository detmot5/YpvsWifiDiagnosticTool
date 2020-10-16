//
// Created by norbe on 16/10/2020.
//

#ifndef WIFIDEBUGGER_DEVICECOMMANDS_H
#define WIFIDEBUGGER_DEVICECOMMANDS_H

#include <Arduino.h>
#include <MillisTimer.h>
#include "DeviceCommand.h"


namespace DeviceCommandsService{
    void init(Stream* deviceStream);
    void send(DeviceCommand& command);
    void process(MillisTimer& tim);
}




#endif //WIFIDEBUGGER_DEVICECOMMANDS_H
