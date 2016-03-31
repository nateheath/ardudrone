# 4. Setup #

## 4.1 Setup your Radio ##

I can't help you much with the setup of your radio besides some general notes. As said before, you need a 6CH transmitter with two sticks and two switches or better a switch and a button.

I have used a standard helicopter model template without mixers and setup the switch/button to suit the needs for the drone as it can be seen in the following picture (I'm using a Multiplex ROYALpro)

![https://ardudrone.googlecode.com/svn/wiki/images/Switch-Button_Example.jpg](https://ardudrone.googlecode.com/svn/wiki/images/Switch-Button_Example.jpg)

## 4.2 Setup the Arduino ##

4.2.1 Go to the Arduino IDE on your computer and open the ArduDroneRC sketch. Also if not already running, enable your RC radio.

4.2.2 Ignore the opened ArduDroneRC\_Sketch file and navigate to the **user\_config.h** file.

4.2.3 First of all, uncomment the following line out. This will enable debug output we need for setup. Remember to comment it out later!

```
//#define DEBUG_LOG_SERIAL
```

4.2.4 Next, navigate to the **WIRING** part and adjust the numbers of the pins to match your setup. These numbers resemble the pins on the arduino where you soldered the according channel wires to.

```
#define THROTTLEPIN     1 // <- Throttle (up-down)
#define ROLLPIN         2 // <- Roll (left-right)
#define PITCHPIN        3 // <- Pitch/Nick (forward-back)
#define YAWPIN          4 // <- Yaw (turn left-right)
#define AUX1PIN         5 // <- Flight Switch (high:fly - low:land)
#define AUX2PIN         6 // <- Emergency Reset Button (high:trigger low:idle)
```

4.2.4 Upload the edited sketch to the Arduino

4.2.5 This time open the serial monitor **Tools > Serial Monitor** and set the baud rate  to **115200** (dropdown lower right). You should start seeing alot of lines with numbers and complaining about moving the sticks to neutral.

---

**NOTE**

**The Arduino sketch has a safety feature that prevents it from connecting to the drone after it has been switched on until both sticks are neutral and the flight switch is set to Land!**

**If the LED is enabled, it will blink >short\_short\_pause< as long as the Ardunio is not ready!**

---


4.2.6 Check if your stick movement matches with the numbers shown in the output. If you move your stick up, the number should go higher (up to about 2000). If you move it down, it should go as low as 950. Center should be around 1500. The channel for flight switch (AUX1) should say about 950 for low and 2000 for high, same for emergency reset (AUX2). If something doesn't match, adjust pin assignment in config file or if a direction seems wrong, invert/adjust channel with your radio.

4.2.7 For further setting up the values in the **INPUT** part of the config file please refer to the great post of the [original YJ-Wifi-Mod](http://www.rcgroups.com/forums/showthread.php?t=1335257&pp=50#post16498030) from Mheeli. The steps described in chapter **5, 6 and 7** of his how-to  comply with the setup required here! The only thing that's new/different is the AUX2/emergency button.

4.2.8 When you are done with setting up the radio values in the user\_config you are almost done and ready to fly. If you want, you could adjust the values found under **BASIC** to suit your needs but I recommend to do this after some flight experience! Do not forget to comment out the ` //#define DEBUG_LOG_SERIAL ` line again! Also, if you do not want to use the built-in LED of the Arduino for status information, comment out the line ` #define DEBUG_LED`, too.

4.2.9 Save your work and upload your sketch one last time to the Arduino. If the upload was successful, disconnect the FTDI from your computer and continue with the next chapter!