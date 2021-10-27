# ESP8266 Alexa to IR controller (transmitter)
This section of the repository demonstrates how to use an ESP-8266 to recieve Alexa commands and transmit corresponding IR commands. Specifically it demonstrates contolling a radiant heater that does not come with any documentation of the IR signals sent.  The NodeMCU Arduino code is available in the [code](/code) folder.

##### The IR codes
I obtained the IR codes by pushing each button on the remote and capturing it with the IR reciever set-up described in the [ir_reciever](../ir_receiver/) folder of this repository. The codes I captured can be seen the [heater_remote_IR_codes](../ir_receiver/heater_remote_IR_codes_v2.txt) file in that folder.  In the Arduino NodeMCU code I used the hexidecimal representation of the IR tramsmissions.

##### In order to make one of these you will need this hardware:
* [NodeMCU v1.0 ESP8266 development board](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES) or other ESP8266 development board
* 555 timer or small signal transistor to drive the LED
* Resistors for the driver part of the output circuit
* IR LED

##### In order to make one of these you will need to install these Arduino libraries
* fauxmoESP.h  2.4.3 This rev is the last rev that simulated a Wemo plug.  Later 3.x versions simulate a Phillip lightbulb.  The code in this repo will not work with 3.x and latter.
  * If you are using a development board like the NodeMCU v1.0 that contains a ESP8266 you will need to also install the ESP8266WiFi library
  * If you development board contains a ESP32 you need to install the WIFI library instead 
* IRremoteESP8266.h
* IRsend.h

When the code is downloaded to the NodeMCU and run it will create three devices that can be discovered by Alexa
* Heater device 1
* Heater device 2
* Heater device 3

To use these devices after adding them through Alexa device discovery, create Alexa routines the use the three devices On/Off states to issue IR commands that can be recieved by the heater
* [Heater control - Alexa and resulting IR commands from the ESP8266](https://docs.google.com/spreadsheets/d/1thoHuIrcbselhGR-zq0jwYt2loby5acfT-mOes6eoRw/edit?usp=sharing) mapping
* [Alexa heater routines](https://1drv.ms/w/s!AkhQRfMv5GmDhSj3fwgvKryUF9b4?e=UReHWI) to make the controller do what you want with the 6 total device states

##### See the controller in action:

[![The Alexa ESP8266 IR controller in action (27 sec)](/assets/Alexa_ESP8286_IR_control_v2_video_image.png)](https://photos.app.goo.gl/GmGifkKtMW2HBMPd7 "The Alexa ESP8266 IR controller in action (27 sec)")

##### Image of the completed controller

![Completed Alexa ESP8266 IR controller](/assets/Alexa_ESP8286_IR_control_v2.png "Completed Alexa ESP8266 IR controller")
