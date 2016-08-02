#include "AlpineRemote.h"
#include "Arduino.h"
#include "String.h"

const uint8_t _cmdStart[3] = {
  0xeb, 0xdb, 0xd5
};

const uint8_t _cmd[3] = {
  0xdb, 0xd6, 0xd5
};

const uint8_t _cmdEnd[2] = {
  0xD5, 0x55
};

AlpineRemote::AlpineRemote(uint8_t pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
  _bitstream = "";
}

void AlpineRemote::sendVolumeUp() {
  AlpineRemote::sendCommand(0xDBD6);
}

void AlpineRemote::sendVolumeDown() {
  AlpineRemote::sendCommand(0x6DF6);
}

void AlpineRemote::sendMute() {
  AlpineRemote::sendCommand(0xADEE);
}

void AlpineRemote::sendPresetUp() {
  AlpineRemote::sendCommand(0xABEF);
}

void AlpineRemote::sendPresetDown() {
  AlpineRemote::sendCommand(0x55FF);
}

void AlpineRemote::sendSourceSelect() {
  AlpineRemote::sendCommand(0xB7DB);
}

void AlpineRemote::sendTrackUp() {
  AlpineRemote::sendCommand(0xBBDA);
}

void AlpineRemote::sendTrackDown() {
  AlpineRemote::sendCommand(0x5DFA);
}

void AlpineRemote::sendPower() {
  AlpineRemote::sendCommand(0x77EB);
}

void AlpineRemote::sendPlayPause() {
  AlpineRemote::sendCommand(0x57FD);
}

void AlpineRemote::sendBandSelect() {
  AlpineRemote::sendCommand(0x6BF7);
}

void AlpineRemote::sendActivateSiri() {
  AlpineRemote::sendCommand(0x7B6E);
}

void AlpineRemote::sendCommand(uint16_t command) {

  // FIXME: This should be sent asynchronously using timer instead.
  //        Also, the timings should probably match up with NEC RF

  // whichEnd is used to decide which end byte should be sent based on the command
  boolean whichEnd = 0;

  _bitstream = "";

  // First send 8ms high
  digitalWrite(_pin, HIGH);
  delay(8);
  // Send 4.5ms low
  digitalWrite(_pin, LOW);
  delayMicroseconds(4500);

  // Send the 3 command init bytes.
  // FIXME: These should be sent in reverse. See below.
  for (byte i=0; i<3; i++) {
    byte data = _cmdStart[i];
    for (byte j=0; j<8; j++) {
      if (_cmdStart[i] & (1<<j)) {
         digitalWrite(_pin, HIGH);
         _bitstream += "1";
      } else {
         digitalWrite(_pin, LOW);
         _bitstream += "0";
      }
      delayMicroseconds(500);
      digitalWrite(_pin, LOW);
      delayMicroseconds(500);
    }
  }

  // Send the 2 command bytes. Because of the way the microprocessor stores variables,
  // we're doing it in reverse, so that the bitstream sent is the assumed one.
  for (int j=15; j>=0; j--) {
    if (command & (1<<j)) {
      digitalWrite(_pin, HIGH);
      whichEnd = 1;
      _bitstream += "1";
    } else {
      digitalWrite(_pin, LOW);
      whichEnd = 0;
      _bitstream += "0";
    }
    delayMicroseconds(500);
    digitalWrite(_pin, LOW);
    delayMicroseconds(500);
  }

  // Send the end of command byte. The last bit is a checksum based on the last bit of
  // the command bytes above, but instead of changing the bit, we're having two end
  // bytes and just choose the correct one depending on the value of whichEnd.
  for (int j=7; j>=0; j--) {
    if (_cmdEnd[whichEnd] & (1<<j)) {
       digitalWrite(_pin, HIGH);
       _bitstream += "1";
    } else {
       digitalWrite(_pin, LOW);
       _bitstream += "0";
    }
    delayMicroseconds(500);
    digitalWrite(_pin, LOW);
    delayMicroseconds(500);
  }
  // FIXME: Create a debug ifdef for logging.
  // Serial.println(_bitstream);
}
