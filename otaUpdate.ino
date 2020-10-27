#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

// The line below is optional. It can be used to blink the LED on the board during flashing
// The LED will be on during download of one buffer of data from the network. The LED will
// be off during writing that buffer to flash
// On a good connection the LED should flash regularly. On a bad connection the LED will be
// on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
// value is used to put the LED on. If the LED is on with HIGH, that value should be passed
//ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

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


void updateFirmware() {
    WiFiClient client;

    // Add optional callback notifiers
    ESPhttpUpdate.onStart(updateStarted);
    ESPhttpUpdate.onEnd(updateFinished);
    ESPhttpUpdate.onProgress(updateProgress);
    ESPhttpUpdate.onError(updateError);

    Serial.printf("Making request");
    t_httpUpdate_return ret = ESPhttpUpdate.update(
        client, "txtin.gs", 80, "/things/update");
    Serial.printf("Back from request");

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        break;

      case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        break;
    }
}
