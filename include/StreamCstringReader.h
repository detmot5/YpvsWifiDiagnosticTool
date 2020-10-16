//
// Created by norbe on 12/10/2020.
//

#ifndef WIFIDEBUGGER_SERIALCSTRINGREADER_H
#define WIFIDEBUGGER_SERIALCSTRINGREADER_H
#include <Arduino.h>



template <uint16 bufferSize>
class StreamCStringReader{
public:
  StreamCStringReader(Stream* stream, void(*strReceivedCallback)(char*), char separator = '\n');
  void run();

private:
  Stream* stream;
  void (*strReceivedCallback)(char*);
  char stringSeparator;       // default \n
  char buffer[bufferSize];
  uint16 bufferIndex;
};

template <uint16_t bufferSize>
StreamCStringReader<bufferSize>::StreamCStringReader(Stream* stream,  void(*strReceivedCallback)(char*), char separator) {
  this->stream = stream;
  this->strReceivedCallback = strReceivedCallback;
  this->stringSeparator = separator;
  bufferIndex = 0;
}

template <uint16_t bufferSize>
void StreamCStringReader<bufferSize>::run() {
  if(stream->available()){
    char c = stream->read();
    if(c == stringSeparator){
      buffer[bufferIndex] = 0;
      bufferIndex = 0;
      if(strReceivedCallback) strReceivedCallback(buffer);
    } else if(bufferIndex >= bufferSize) {
      bufferIndex = 0;
    } else {
      buffer[bufferIndex] = c;
      bufferIndex++;
    }
  }
}







#endif //WIFIDEBUGGER_SERIALCSTRINGREADER_H
