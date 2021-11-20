// This code uses fauxmoESP version 2.4.3 to emulate a Wemo plug. It will need to be modified to use
// newer fauxmoESP libraries since fauxmoESP changed in Version 3 to emulating a Phillips light.
// the 3.0 version and later have the advanage that the 2.4.3 version could only add three devices
// to Alexa for a total of 6 unique commands per IP address.  THe newer implementation can provide 
// hundreds of cammands as it implements the dimming from 1-100 levels.  That is a great advantage.
// The code here will compile with the newer libraries but alas Alexa was unable to detect them. Therefore,
// this code should only be compliled with fauxmoESP 2.4.3.

#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "credentials.h"  // copy the credentials.sample.h file and add your 
                          // WIFI SSID and password to make a credentials.h file

#define SERIAL_BAUDRATE                 115200
#define LED                             4

fauxmoESP fauxmo;

unsigned int heat_on_off = 0xFFA25D;
unsigned int _500_watts  = 0xFFA857;
unsigned int _1000_watts = 0xFF18E7;
unsigned int _1500_watts = 0xFF4AB5;
unsigned int timer = 0xFFE817;
unsigned int heat_count = 3;

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to send the IR message.

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}

void setup() {

    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println();
    Serial.println();

    // Wifi
    wifiSetup();

    // LED test
    // pinMode(LED, OUTPUT);
    // digitalWrite(LED, HIGH);

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    fauxmo.addDevice("Heater device 1");
    fauxmo.addDevice("Heater device 2");
    fauxmo.addDevice("Heater device 3");

    // fauxmoESP 2.0.0 has changed the callback signature to add the device_id,
    // this way it's easier to match devices to action without having to compare strings.

    // Callback to retrieve current state (for GetBinaryState queries)
    fauxmo.onGetState([](unsigned char device_id, const char * device_name) {
        return !digitalRead(LED);
    });

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state) {
        // Logic for transmitting IR commands when Alexa command is to Heater device 1    
        if (strcmp(device_name, "Heater device 1") == 0) {
          Serial.println("");
          Serial.print("Heater Device 1:");
          Serial.print(state);
          Serial.println("");
          if (state) {
            Serial.println("Heater init");
            irsend.sendNEC(heat_on_off);
            delay(1000);
            Serial.println("1000 watts");
            irsend.sendNEC(_1000_watts);
            delay(1000);
            Serial.println("Timer On with 1 hr");
            irsend.sendNEC(timer);  // Send first to trigger heater to await timer command
            delay(1000);
            irsend.sendNEC(timer);  // Send again to trigger heater to add one hr to the timer
              
            //delay(300);   // Uncomment to test LED by leaving it on 
            //digitalWrite(LED, HIGH);   // Uncomment to test LED by leaving it on
              
            }
          else {
            Serial.println("Heater Off");
            irsend.sendNEC(heat_on_off);
            //delay(300);
            //digitalWrite(LED, LOW); //LED Test
            }
          }
    
        // Logic for transmitting IR commands when Alexa command is to Heater device 2
        if (strcmp(device_name, "Heater device 2") == 0) {
          Serial.println("");
          Serial.print("Heater Device 2:");
          Serial.print(state);
          Serial.println("");
          if (state) {
            Serial.println("500 watts");
            irsend.sendNEC(_500_watts);      
            }
          else {
            Serial.println("1000 watts");
            irsend.sendNEC(_1000_watts);  
            }
          }
    
        // Logic for transmitting IR commands when Alexa command is to Heater device 3
        if (strcmp(device_name, "Heater device 3") == 0) {
          Serial.println("");
          Serial.print("Heater device 3:");
          Serial.print(state);
          Serial.println("");
          if (state) {
            Serial.println("1500 watts");
            irsend.sendNEC(_1500_watts);      
            }
          else {
            irsend.sendNEC(timer);
            delay(1000);
            irsend.sendNEC(timer);  // Send again to trigger heater to add one hr to the timer
            }
          }
    });    

}

void loop() {

    // Since fauxmoESP 2.x the library uses the "compatibility" mode by
    // default, this means that it uses WiFiUdp class instead of AsyncUDP.
    // The later requires the Arduino Core for ESP8266 staging version
    // whilst the former works fine with current stable 2.3.0 version.
    // But, since it's not "async" anymore we have to manually poll for UDP
    // packets
    
    fauxmo.handle();

    static unsigned long last = millis();
    if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }

}
