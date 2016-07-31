# arduino-alpine-remote
An Arduino library to control an alpine car audio head unit via a 3.5 remote wire.

## Known issues
This library is currently lacking in documentation, and is completely syncronous. That means it will lock up your Arduino in order to get the timing right. This will be rewritten for asynchronous operation using timers as soon as possible. Also, the NEC IR protocol seems to be the basis for this protocol as well, but the timings are not specifically tested for this. This needs more work.

## Compatibility
It is specifically written and tested for the iLX-700/iLX-007, but the protocol seems to be the same for most if not all Alpine head units. Please let me know if you have tested this successfully on another model, and I will add it to the list!

## Protocol
The protocol used seems to be a version of the NEC IR protocol (see https://www.drive2.com/l/3711116/ for more info) but with several discrepancies. Thanks to Youtube user moserlukas051194 for bringing this to my attention! I will document a bit more about what I know here later on.

## Acknowledgements
This is based on information on the protocol coming from an old thread (including code) at mp3car.com:
http://www.mp3car.com/forum/mp3car-technical-hardware/input-devices/134542-need-alpine-wired-remote-control-pinout
I have used some of the code there to put together this library, but most importantly, the protocol description. All credit for the protocol detection and basic setup goes to user FordNoMore.
