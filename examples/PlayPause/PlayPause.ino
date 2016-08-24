/*
  PlayPause

 Alternates between writing play and pause to the Alpine head unit
 every three seconds.


 The circuit:
 3.5mm phono jack tip connected to pin 3 on the Arduino.

 created 2016
 by Mattias Winther <mattias.winther@gmail.com>

 This example code is based on the Button example for the Arduino and is released
 in the public domain.

 */

#include "AlpineRemote.h"

// constants won't change. They're used here to
// set pin numbers:
const int alpinePin =  3;      // the number of the Alpine +5V pin (the tip of the 3.5mm plug)

// initialize an AlpineRemote instance:
AlpineRemote alpine(alpinePin);

void setup() {
}

void loop() {
  alpine.writePlayPause();
  delay(3000);
}
