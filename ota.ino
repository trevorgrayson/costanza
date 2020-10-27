/**
   httpUpdate.ino
   MAC: a0:20:a6:27:0b:b2

    Created on: 27.11.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include "pins.h"

#ifndef APSSID
#define APSSID ""
#define APPSK  ""
#endif

ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
  viewSetup();

  clear();
  print("hello.");
  viewRender();

  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(APSSID, APPSK);
  Serial.println("AP added!!!");
  print("starting...");
  viewRender();
}

bool updateChecked = false;
bool isConnected() {
  return WiFiMulti.run() == WL_CONNECTED;
}

void loop() {
  if (!updateChecked && isConnected()) {
    updateChecked = true;
    Serial.println("checking for updates.");
    clear();
    print("found update...");
    viewRender();
    updateFirmware();
    clear();
    print("done.");
    viewRender();
    return;
  } 
  clear();
  print("v1.0.5");
  viewRender();
}
