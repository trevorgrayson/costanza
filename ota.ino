/**
   httpUpdate.ino
   MAC: a0:20:a6:27:0b:b2

    Created on: 27.11.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#ifndef APSSID
#define APSSID "iou"
#define APPSK  "iou"
#endif

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  viewSetup();

  clear();
  print("bootloading...");
  viewRender();
  delay(4000);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("dont you know", APPSK);
  Serial.println("AP added!!!");
  print("starting...");
  viewRender();
  delay(5000);
}

void updateStarted() {
  Serial.println("CALLBACK:  HTTP update process started");
  clear();
  print("started");
  viewRender();
}

void updateFinished() {
  Serial.println("CALLBACK:  HTTP update process finished");
  clear();
  print("finished");
  viewRender();
}

void updateProgress(int cur, int total) {
  Serial.printf("CALLBACK:  HTTP update process at %d of %d bytes...\n", cur, total);
  clear();
  print("updating");
  viewRender();
}

void updateError(int err) {
  Serial.printf("CALLBACK:  HTTP update fatal error code %d\n", err);
  clear();
  print("fatal");
  viewRender();
}

void loop() {
  clear();
  // wait for WiFi connection
  Serial.print(".");
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    updateFirmware();
  } else {
      clear();
      print("nah");
      viewRender();
  }
  Serial.println("!");
}

