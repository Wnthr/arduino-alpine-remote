/*
  AlpineRemote.h - Library for interfacing with an Alpine
  car audio unit as a wired remote.
  Created by Mattias Winther, July 31, 2016.
  Released into the public domain.
*/
#ifndef AlpineRemote_h
#define AlpineRemote_h

#include "Arduino.h"

class AlpineRemote
{
  public:
    AlpineRemote(uint8_t pin);

    void sendVolumeUp();
    void sendVolumeDown();
    void sendMute();
    void sendPresetUp();
    void sendPresetDown();
    void sendChangeSource();
    void sendTrackUp();
    void sendTrackDown();
    void sendPower();
    void sendPlay();
    void sendBandProg();

    void sendCommand(int command);

  private:
    uint8_t _pin;
};

#endif
