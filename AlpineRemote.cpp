#include "Arduino.h"
#include "AlpineRemote.h"

AlpineRemote::AlpineRemote(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void AlpineRemote::sendCommand(int command) {
    return command;
}
