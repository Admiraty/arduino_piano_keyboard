# arduino_piano_keyboard
Read an 88 key ( 176 button ) matrix and send to serial interface changes.


It works with 8x8 keys.

on raspberry pi I am running : 
   fluidsynth -a alsa /usr/share/sounds/sf2/FluidR3_GM.sf2 < /dev/ttyUSB0

   

== Known issues ==
1. There are 88 keys on a piano, not 32
2. After several hours, the arduino stops reporting key presses and only reports key releases
