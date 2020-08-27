#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESP32Ping.h>
#define MDASH_APP_NAME "TestAppUN"
#include <mDash.h>
#define DEVICE_PASSWORD "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

#define ESP_getChipId()   ((uint32_t)ESP.getEfuseMac())

const char* remote_host = "www.google.com";

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

  // put your setup code here, to run once:
  Serial.begin(115200);

  // WiFi.mode(WiFi_STA); // it is a good practice to make sure your code sets wifi mode how you want it.

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  //reset settings - wipe credentials for testing
  //wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap

  String chipID = String(ESP_getChipId(), HEX);
  chipID.toUpperCase();

  String AP_SSID = "UNPOD-" + chipID;
  String AP_PASS = "passcode";

  res = wm.autoConnect(AP_SSID.c_str(), AP_PASS.c_str()); // password protected ap
  //res = wm.autoConnect("AutoConnectAP", "password"); // password protected ap

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  mDashBegin(DEVICE_PASSWORD);

}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin();
  }

  if (Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }

  delay(2000);
}
