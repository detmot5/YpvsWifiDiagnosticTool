//
// Created by norbe on 16/10/2020.
//

#ifndef WIFIDEBUGGER_RINGBUFFER_H
#define WIFIDEBUGGER_RINGBUFFER_H

#include <Arduino.h>

template <typename T, uint16_t buf_size>
class RingBuffer{
public:
  RingBuffer();

  void pushBack(T& element);
  bool getFront(T* element);
  uint16_t size() const {return buf_size;}

private:
  T elements[buf_size];
  uint16_t head;
  uint16_t tail;
};

template <typename T, uint16_t buf_size>
RingBuffer<T, buf_size>::RingBuffer(){
  head = 0;
  tail = 0;
}


template <typename T, uint16_t buf_size>
void RingBuffer<T, buf_size>::pushBack(T& element){
  uint16_t nextHead = this->head + 1;
  if(nextHead >= buf_size) nextHead = 0;
  if(nextHead == this->tail) this->tail = 0;
  this->elements[nextHead] = element;
  this->head = nextHead;
}
template <typename T, uint16_t buf_size>
bool RingBuffer<T, buf_size>::getFront(T* element){
  if(this->head == this->tail) return false;
  this->tail++;
  if(this->tail == buf_size);
  *element = this->elements[this->tail];
  return true;
}


#endif //WIFIDEBUGGER_RINGBUFFER_H
