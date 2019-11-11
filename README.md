# arduino_piano_keyboard


# What : 
Read an 66 key ( 128 button ) matrix and send changes in statuses to serial device.

This is a sketch written for the Arduino mega 2560. It scans the 8x16 matrix keyboard, and returns the results as valid commands that can be pipped into fluidsynth.


# Use
On general purpose computer I am running : 

   # Set serial speed
   stty -F 9600

   # Read from the serial interface and feed it to fluidsynth
   fluidsynth -a alsa /usr/share/sounds/sf2/FluidR3_GM.sf2 < /dev/ttyUSB0




# Use on Raspberry Pi 4
I am running it on raspberry pi 4, on it I have a file /bin/piano which contains :

   stty -F 9600
   taskset 0xe fluidsynth -a alsa /usr/share/sounds/sf2/FluidR3_GM.sf2 -c4 < /dev/ttyUSB0 > /dev/null

I run this as a service, arduino plugged into raspberry pi ( USB )

With the default raspbian, I was getting audio artefacts, I changed the fluidsynth command to '-c4' instead of '-c8 -z64'; I also recompiled the kernel with the rt_patches. Now my fluidsynth runs smooth without artefacts and without noticeable lag.

 
   
   


