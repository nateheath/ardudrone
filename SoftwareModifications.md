# 3. Software modifications #

If you haven't done it already, download the [latest package](http://code.google.com/p/ardudrone/downloads/list) with all required files for this mod and unzip it somewhere on your computer.

## 3.1 Drone ##


3.1.1 First we need to upload some files to the drone. Power it up and connect to it with your computer via WiFi as you would do with your iDevice (might have to unpair it first). Use any FTP application and connect to:

```
192.168.1.1
```

Now upload the provided _{folder\_you\_unzipped\_to}/ardudrone/_ folder. Double check that for any file binary mode is used to transfer it! When all files are uploaded close the FTP application.

3.1.2 Next step is some setup on the drone itself via console. Again connect to your drone but this time with telnet. For this open **Terminal** on Mac or **cmd** on Windows and type (omit the #):

```
# telnet 192.168.1.1
```

You should be greeted with something like this

```
BusyBox v1.14.0 (2010-07-02 15:17:06 CEST) built-in shell (ash)
Enter 'help' for a list of built-in commands.

#
```

3.1.3 Now we need to setup some files we just uploaded. We must make **ardudrone\_setup.sh** and **atcomproxy\_arm** executable with commands seen below:

```
# cd /data/video/ardudrone
# chmod 755 ardudrone_setup.sh
# chmod 755 atcomproxy_arm 
```

To check our work, use the command **ls -lisa**, there should be three _x_ in the third colum of its output:

```
# ls -lisa
    111    0 drwxr-xr-x    2 root     root          600 Jan  1 00:52 .
     65    0 drwxr-xr-x    4 root     root          504 Jan  1 00:52 ..
    124    4 -rwxr-xr-x    1 root     root          821 Jan  1 00:49 ardudrone_setup.sh
    127   16 -rwxr-xr-x    1 root     root        12494 Jan  1 00:49 atcomproxy_arm
    125  876 -rw-r--r--    1 root     root       896291 Jan  1 00:49 dwc_otg.ko
    128  248 -rw-r--r--    1 root     root       250284 Jan  1 00:49 ftdi_sio.ko
    126    8 -rw-r--r--    1 root     root         6421 Jan  1 00:49 libioctl_arm.so
    129  340 -rw-r--r--    1 root     root       347714 Jan  1 00:49 usbserial.ko
```

3.1.4 Next test if the proxy app is working:

```
# ./atcomproxy_arm -v -d /dev/tty
./atcomproxy_arm > Proxy Ready: Waiting for data in /dev/tty to send to 192.168.1.1:5556!
```
Type in the following line (or copy&paste)
```
AT*LED=1,2,1073741824,3
```
Result should be:
```
./atcomproxy_arm > AT*LED=1,2,1073741824,3!

[LEDS ON THE DRONE SHOULD BLINK FOR 3S!]

[EXIT WITH CTRL+C]
```


If you get a "Segmentation fault" the binary was probably uploaded wrong as ASCII, retry in binary format!

3.1.5 Check if the startup script runs:

```
# ./ardudrone_setup.sh
```


You should see the following output, the last lines throw some error messages, this is ok since we did not yet connect the Arduino. For us right now is only important that the script itself runs and the modules get loaded without problems.

```
Enabling USB, powering up Arduino and launching AT Commands Proxy
Loading usbserial.ko
Loading ftdi_sio.ko
Enabling USB Port
Loading dwc_otg.ko
Waiting 3s for the device to be ready
Setting correct baud rate of 115200 for /dev/ttyUSB0
[SOME ERROR MESSAGE ABOUT DEVICE NOT FOUND, IS OK AT THIS TIME]
Launching AT Command Proxy server
[SOME ERROR MESSAGE ABOUT DEVICE NOT FOUND, IS OK AT THIS TIME]
```


If you see any other errors, make sure you uploaded the files correctly and and your drone runs on firmware 1.3.3!


3.1.6 **OPTIONAL but RECOMMENDED** Make backups of system files we want to change

3.1.6.1 Create folder backup/ in /data/video

```
# mkdir /data/video/backup
```

3.1.6.2 Copy system scripts to make backups

```
# cp /bin/check_update.sh /data/video/backup/
# cp /etc/init.d/rcS /data/video/backup/
```

3.1.7 Now we have to edit two system scripts to enable the USB port at startup and launch our proxy application.


---

**WARNING**

**This is the most critical part of the mod. If you mess anything up in these scripts your drone might not boot anymore and is bricked. Your only rescure is to reflash it with an USB-Cable or the Parrot support (but I do not know if they help you if you trashed the system files ;). You have been warned.**

**NOTE**

**Exactly follow these instructions, stuff in brakets is either a key(s) you have to press or an action for you to do.**

---


3.1.7.1 **rcS**: We have to add the following line

```
/data/video/ardudrone/ardudrone_setup.sh
```

in the file **/etc/init.d/rcS**.

For this do the following:

```
# vi /etc/init.d/rcS

[MOVE WITH CURSOR TO LINE 54]
[i]
[INSERT LINE BY TYPING or COPY&PASTE]
[RETURN]
[ESC]
[:]
[wq]
[ENTER] 
```

It should look like this:

```
...
/bin/wifi_setup.sh                                                  
                                                                   
# Patch to enable button management.                                
ln -s /dev /dev/input                                               
                                                              
/data/video/ardudrone/ardudrone_setup.sh
                                                              
#mount -o nolock,proto=tcp -t nfs 192.168.0.11:/mnt/video /home/default
/bin/check_update.sh                                                   
...
```


3.1.7.2 **check\_update.sh**: Now we need to add the following line

```
export LD_PRELOAD=/data/video/ardudrone/libioctl_arm.so
```

at the top of the script **/bin/check\_update.sh**.

To do so do the following:

```
# vi /bin/check_update.sh

[MOVE WITH CURSOR TO LINE 2]
[i]
[RETURN]
[INSERT LINE BY TYPING or COPY&PASTE]
[RETURN]
[ESC]
[:]
[wq]
[ENTER]
```

It should look like this:

```
#!/bin/sh

export LD_PRELOAD=/data/video/ardudrone/libioctl_arm.so

UPDATE_PATH=/update/ardro…

```

3.1.8 Make sure the changes are written to flash by typing

```
# sync
```

3.1.9 Check your modified scripts by typing

```
# cat /etc/init.d/rcS 
[YOUR MODIFIED SCRIPT SHOULD OUTPUT]

# cat /bin/check_update.sh
[YOUR MODIFIED SCRIPT SHOULD OUTPUT]
```


If everything looks good and you are absolutely sure you did as it was described here, reboot  the drone. It should start and behave like normal, if not, its time to get your USB-Flash-Cable ready ;)!  If you see no problems, continue.


## 3.2 Arduino ##

In this step we have to program the Arduino with our software (called _sketch_) provided in the .zip file you downloaded. Don't be afraid, this is not as complicated as it sounds!

> 3.2.1 Download and install the [Arduino IDE](http://arduino.cc/en/Main/Software)

> 3.2.2 Launch it and and open the Arduino sketch found in _{folder\_you\_unzipped\_to}/ArduDroneRC\_Sketch/_

> 3.2.3 Setup our Arduino by selecting **Tools > Board > Arduino Pro or Pro Mini (5V, 16 MHz) w/ ATmega328**

> 3.2.3 Take a regular USB Cable and connect the FTDI basic breakout to your computer.

> 3.2.4 Select the device in **Tools > Serial Port > {FTDI Device}** _(The exact naming depends on your system, but you should spot it! If you can't, you might need to install additional drivers!)_

> 3.2.5 Plug the Arduino into the FTDI basic breakout

> 3.2.6 Select **File > Upload to I/O Board** to send the sketch to the Arduino. This takes a few seconds but when everything went fine it should start to blink in a rhythm.


Were almost done! We still have to adjust some values so keep the Arduino connected. We will setup it in the next chapter using the Arduino IDE!