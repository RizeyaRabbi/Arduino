#include <WiFi.h>
#include <PubSubClient.h>
#include "freertos/timers.h"

//---- WiFi settings
//const char ssid[] = "Esp32Test";
//const char password[] = "1234567890";
const char* ssid = "atilimited.net2";
const char* password = "AtiL2@2021#";

//---- MQTT Broker settings
const char* mqtt_server = "91.121.93.94";
const char* mqtt_username = "";
const char* mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const uint8_t
sensor0_washRoom1 = 23, // D23
sensor1_washRoom1 = 22, // D22
sensor2_washRoom1 = 21, // D21
sensor3_washRoom1 = 19, // D19
sensor0_mainRoom = 4,   // D4
sensor1_mainRoom = 16,  // RX2
sensor2_mainRoom = 17;  // TX2

void reconnect() {
  // Loop until we’re reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    String clientId = "ESP32Client-";  //random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // subscribe the topics here
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");  // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage;
  for (int i = 0; i < length; i++)
  {
    incommingMessage += (char)payload[i];
  }

}
class SmartOffice
{
  private:
    bool motion = false, deviceON = false, delayRunning = false, logFlag = false;
    uint64_t startDelay, delayTime, startInterval, timeOn, logStart, logStop, logValue,
             intervalTime, secondInOneMinute = 60, microsecondInOneSecond = 1000000;

  public:
    void controller(uint8_t _sensor0, const char*_topic, const char *_name, uint64_t _delayTime)
    {
      delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
      uint8_t sensorStatus0 = digitalRead(_sensor0);
      if (sensorStatus0 == HIGH)
      {
        motion = true;
        if (!deviceON)
        {
          deviceON = true;
          client.publish(_topic, "1");
          if (!logFlag)
          {
            logStart = esp_timer_get_time();
            logFlag = true;
            Serial.print(_name);
            Serial.print(" ");
            Serial.print("Turned On");
            Serial.print("\n");
          }
        }
        if (deviceON)
        {
          delayRunning = false;
        }
      }
      if (sensorStatus0 == LOW && deviceON)
      {
        motion = false;
        if (!delayRunning)
        {
          startDelay = esp_timer_get_time();
          delayRunning = true;
        }
      }
      if (!motion && (esp_timer_get_time() - startDelay >= delayTime))
      {
        if (deviceON)
        {
          deviceON = false;
          delayRunning = false;
          client.publish(_topic, "0");
          if (logFlag)
          {
            logStop = esp_timer_get_time();
            logValue = (logStop - logStart) / 1000000UL;
            Serial.print(_name);
            Serial.print(" ");
            Serial.print(" Turned Off and was On for:");
            Serial.print(" ");
            Serial.print(logValue);
            Serial.print(" ");
            Serial.print("Seconds");
            Serial.print("\n");
            logFlag = false;
          }
        }
      }
    }
    void interval(uint64_t _intervalTime, void (&function)())
    {
      intervalTime = _intervalTime * microsecondInOneSecond;
      if (esp_timer_get_time() - startInterval >= intervalTime)
      {
        function();
        startInterval = esp_timer_get_time();
      }
    }
};
SmartOffice c[5];
void setup() {
  Serial.begin(115200);
  pinMode(sensor0_washRoom1, INPUT_PULLUP);
  pinMode(sensor1_washRoom1, INPUT_PULLUP);
  pinMode(sensor2_washRoom1, INPUT_PULLUP);
  pinMode(sensor3_washRoom1, INPUT_PULLUP);
  pinMode(sensor0_mainRoom, INPUT_PULLUP);
  pinMode(sensor1_mainRoom, INPUT_PULLUP);
  pinMode(sensor2_mainRoom, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  Serial.print("\nCalibrating Sensor: ");
  for (int i = 0; i < 30; i++) {
    digitalWrite(2, LOW);
    Serial.print(".");
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);
  }
  Serial.print("\nConnecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(1000);
  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  smartOfficeController();
}
void smartOfficeController() {
  c[0].controller(sensor0_washRoom1, "DS/4TF_WRL", "4TF_WRL", 2);
  c[1].controller(sensor3_washRoom1, "DS/4TF_WRE", "4TF_WRE", 2);
  c[2].controller(sensor0_washRoom1, "DS/4TF_MRL0", "4TF_MRL0", 2);
  c[3].controller(sensor1_washRoom1, "DS/4TF_MRL1", "4TF_MRL1", 2);
  c[4].controller(sensor2_washRoom1, "DS/4TF_MRL2", "4TF_MRL2", 2);
  c[0].interval(10,wifiReconnect);
}
void wifiReconnect() {
  if ((WiFi.status() != WL_CONNECTED)) {
    Serial.println("Reconnecting.");
    WiFi.begin(ssid, password);
  }
}
