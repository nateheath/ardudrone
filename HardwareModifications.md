# 2. Hardware modifications #



## 2.1 On the Drone ##

Remove the rubber protector from the USB service port on the bottom.

Done.

:)

## 2.2 Making a Cable ##

The first thing we make is the cable to connect the Arduino over the FTDI breakout board to the drone. For this we need the USB cable and the molex plug (or whatelse you bought). Take the side with the Mini-USB Type B plug and cut it of with about 10cm of cable left to it (depending on where you want to place the Arduino and receiver on the drone). **Note: Keep the other end! With a second molex connector you can put together an emergency  USB Flash Cable! You know, just in case ;)**

Now lay open the single wires, you should see four of em: black/red/white/green. Black is ground, red is +V, green is Data+ and white is Data-. Connect/solder these to the molex plug in the order as shown below:

![https://ardudrone.googlecode.com/svn/wiki/images/CableUSB.png](https://ardudrone.googlecode.com/svn/wiki/images/CableUSB.png)

In case you wonder about picture (2), I couldn't get the molex plug and used **2x20 2.00mm (.079") pitch break away double row female headers** (with swiss round machined pins) to make the plug. That's what you see there! :)

### (USB Flash Cable) ###

If you have a second molex plug and a bit of spare time left, you can make an USB Flash Cable. Below you can see  the official guide from Parrot that shows the pin-layout of this cable. As you can see it's actually the same we used for our first cable. So repeat your work from above with the other end of the cable et voilà: Flash Cable :)

![https://ardudrone.googlecode.com/svn/wiki/images/ARDrone-USB-Cable.png](https://ardudrone.googlecode.com/svn/wiki/images/ARDrone-USB-Cable.png)



## 2.3 Getting the Arduino ready ##

### 2.3.1 Solder a Header ###

Solder a 6-pin header to the short end of the Arduino. This will be used to connect it to the FTDI Breakout Board to either flash it or talk to the drone.

![https://ardudrone.googlecode.com/svn/wiki/images/arduino_header.jpg](https://ardudrone.googlecode.com/svn/wiki/images/arduino_header.jpg)

### 2.3.2 Connect the Receiver to the Arduino ###

The following connections must be made between your receiver and the Arduino: (LED just highlighted for illustration!)

![https://ardudrone.googlecode.com/svn/wiki/images/ArduinoWiring.jpg](https://ardudrone.googlecode.com/svn/wiki/images/ArduinoWiring.jpg)

The Arduino supplies **+5V** on the **VCC** pin and **(-)** on the free **GND** pins. Connect these two to the BEC input of your receiver. How exactly your receiver accepts power highly dependends on the actual model, please check your manual for details!

To get the signals from CH1 - CH6, we only need to connect the **servo signal cable** of each channel to the Arduino. Which cable carries the signal depends on the manufacturer of your receiver, usually this is the white or orange wire! Please again check the manual for details!

**Examples for signal lines:**

![https://ardudrone.googlecode.com/svn/wiki/images/ServoSignalWiring.jpg](https://ardudrone.googlecode.com/svn/wiki/images/ServoSignalWiring.jpg)

These signal wires must be connected to the I/O pins of the Arduino. It has 13 pins (numbered 1 - 13) of wich we need 6, one for each channel of your RC receiver. Solder the signal outputs of your receiver to any of the numbered pins on the Arduino as in the wiring illustration shown above.

Note: Try to **avoid using Pin 13**, if you **want to use the built-in LED** of the Arduino. This pin is shared with the LED!

### 2.3.3 Result ###

That's it with the soldering, you should now have something like this:

**(USB Cable - FTDI Basic Breakout - Arduino - RC Receiver)**

![https://ardudrone.googlecode.com/svn/wiki/images/cable_ftdi_arduino_receiver_disconnected.jpg](https://ardudrone.googlecode.com/svn/wiki/images/cable_ftdi_arduino_receiver_disconnected.jpg)