# ESP8266 Alexa to IR controller
This repository demonstrates how to use an ESP-8266 to recieve Alexa commands and transmit corresponding IR commands. Specifically it demonstrates controlling a radiant heater that does not come with any documentation of the IR signals sent. However the code and technique can be leveraged for any IR device you want to control.

This repository assumes you know how to use the Arduino IDE and program an Arduino.  I used an [NodeMCU 1.0 ESP8266 development board](https://www.amazon.com/NodeMCU-ESP8266-Breakout-Arduino-Makerdo/dp/B07BGCF3NY) however this code can be used with other ESP8266 development boards such as the [Adafruit HUZZAH ESP8266 Breakout](https://www.adafruit.com/product/2471)

##### The implementation described here controls a radiant heater which comes with an IR remote. This repository contains two code sections
1. [ir_receiver](/ir_receiver) - Circuit and code to detect the IR command signals sent from the IR remote
2. [alexa_ir_controller](/alexa_ir_controller) (transmitter) - Circuit and code to use an ESP8266 to recieve Alexa commands and then issue the corresponding IR commands through an IR LED

##### See the controller in action:

[![The Alexa ESP8266 IR controller in action (27 sec)](/assets/Alexa_ESP8286_IR_control_v2_video_image.png)](https://photos.app.goo.gl/GmGifkKtMW2HBMPd7 "The Alexa ESP8266 IR controller in action (27 sec)")

##### Image of the completed controller

![Completed Alexa ESP8266 IR controller](/assets/Alexa_ESP8286_IR_control_v2.png "Completed Alexa ESP8266 IR controller")
Yeah, I know that looks like a cold solder joint but it is working reliably so I am leaving it as is.
