# 5. Fly :) #

Nervous already? No wonder, It's about time to get our modded drone airborne! If not already done, fix the FTDI/Arduino and the receiver to the drone eg. with some tape.

## 5.1 Switch on your radio, move sticks to center and the fly switch to land ##

## 5.2 Connect the Arduino with the custom cable to the USB port at the bottom of the drone ##

## 5.3 Start up your drone and wait... ##

The drone is now booting. If everything went fine the lights on the Arduino/FTDI should flash on after some seconds and the receiver starts working. Also the lights on the engines and the bottom LED of the drone should switch green. When your sticks are centered and the flight switch set to land, the Arduino connects to the drone and initializes it. As soon this is done, the LEDs on the engines blink red/green for a few seconds. This is the signal that everything is ready to...

## 5.4 Fly! ##

Toggle the fly switch and watch the drone, it should raise in the air and hover like normal. Test your stick input with brief movements, especially check directions so nothing is inverted! Land the drone by switching the fly switch back off. Test the emergency reset button by pressing it, the lights should turn red. Press it again and they should turn back green. (You can test this in the air also but it results in a hard landing! **Outch**). Also you can tilt the drone by 90°, the angle protection should kick in and the LEDs turn red. Again, reset the drone with the emergency reset button. If everything seems ok, you are done! Congratulations on your RC controlled AR.Drone!

---

**That's it! Have fun flying and good luck with your drone! Check back for updates!**

**If you encounter any issues or have any suggestions, [tell me](http://code.google.com/p/ardudrone/issues/entry)! :)**

---

![https://ardudrone.googlecode.com/svn/wiki/images/ArduDrone_Finished.jpg](https://ardudrone.googlecode.com/svn/wiki/images/ArduDrone_Finished.jpg)