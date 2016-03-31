# Introduction #

Let me start with a warning:

**This mod is not for the faint of heart, you will have to modify critical system configs and if you mess this up, you might brick your drone!**

If you have some experience with RC, soldering and basic knowledge of using terminal read on! If not, stick with flying your drone with your favourite iDevice :)

## Thanks ##

Thank you to a lot of nice people without them this would not have been possible!
  * [Mheeli](http://www.rcgroups.com/forums/member.php?u=10627) for creating the original Wifi-version of this mod and inspiring me to do this
  * [MAPGPS](http://www.rcgroups.com/forums/member.php?u=335286) for all his work on the AR.Drone especially enabling the USB port and his great help and advise all the time!
  * [scorpion2k](http://embedded-software.blogspot.com/) for literally saving my drone twice from being a brick ;) His research on creating a custom kernel as well enabling USB and his great [tools](http://code.google.com/p/ardrone-tool/) were essential!


## How it works ##

To control your AR.Drone with a regular RC Radio, we have to translate the signals used by the RC gear into commands understandable by the drone. The translated commands (_AT Commands_) are then sent to the controlling program running on the drone. This is actually a server that accepts any commands it receives over network (usually from your iDevice over WiFi).

This happens in two steps:
  1. An Arduino board reads the RC signals and translates them. They are then send over a serial connection to the drone.
  1. On the drone itself waits an additional small proxy application redirecting any commands it receives to the commands server (called _program.elf_).

To connect the Arduino to the drone and also to power it (and your RC Receiver!) we use the USB service port on the bottom of the drone. This actually contains two interfaces: an -by default disabled- USB port and a serial port. Both can be used for this mod but both have its pros and cons. To make things easy for now, I will only describe the mod using the USB connection! I might add the serial version later…


## Notes ##

This mod currently **only works** with AR.Drone firmware **version 1.3.3**. If you want to do the mod and do not have this version installed, you have to down-/upgrade to this version. Unfortunately, we must wait until Parrot releases the sources for the new firmwares to compile all required tools for the latest version!

Most images used are for illustration purposes only. Used images and trademarks are copyright of their respective owners.