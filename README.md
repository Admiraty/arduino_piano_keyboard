# arduino_piano_keyboard


Read an 66 key ( 128 button ) matrix and send changes in statuses to serial device.


It works with 8x16 keys.

on raspberry pi I am running : 

   # Set serial speed
   stty -F 9600

   # Read from the serial interface and feed it to fluidsynth
   fluidsynth -a alsa /usr/share/sounds/sf2/FluidR3_GM.sf2 < /dev/ttyUSB0

   

== Known issues ==
1. There are 88 keys on this piano, but only 66 work

