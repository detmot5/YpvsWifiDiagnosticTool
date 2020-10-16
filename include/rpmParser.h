//
// Created by norbe on 12/10/2020.
//

#ifndef WIFIDEBUGGER_RPMPARSER_H
#define WIFIDEBUGGER_RPMPARSER_H
#include <SoftwareSerial.h>


void ypvsRpmQuery(SoftwareSerial&  serial);

void createJsonFromRPM(char* string);

char* getRPMInJSON();
#endif //WIFIDEBUGGER_RPMPARSER_H
