#include <WiFi.h>
#include <PubSubClient.h>
#include "freertos/timers.h"

//---- WiFi settings
const char ssid[] = "Esp32Test";
const char password[] = "1234567890";

//---- MQTT Broker settings
const char *clientId = "ESP32Sender-0";
const char *mqtt_server = "91.121.93.94";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const uint8_t
    sensor0_washRoom1 = 14,
    sensor1_washRoom1 = 27,
    sensor2_washRoom1 = 21,
    sensor3_washRoom1 = 19,
    sensor0_mainRoom = 26,
    sensor1_mainRoom = 25,
    sensor2_mainRoom = 17;

uint8_t reconnectCounter = 0;

void reconnect()
{
    // Loop until we’re reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection…");
        // Attempt to connect
        if (client.connect(clientId, mqtt_username, mqtt_password))
        {
            Serial.println("connected");
            digitalWrite(2, HIGH);
            delay(2000);
            // subscribe the topics here
        }
        else
        {
            reconnectCounter += 1;
            digitalWrite(2, LOW);
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 2 seconds");
            if (reconnectCounter == 5)
            {
                WiFi.begin(ssid, password);
                reconnectCounter = 0;
            }
            delay(2000);
        }
    }
}
class SmartOffice
{
private:
    bool motion = false, deviceON = false, delayRunning = false, logFlag = false;
    uint64_t startDelay, delayTime, startInterval, timeOn, logStart, logStop, logValue,
        intervalTime, secondInOneMinute = 60, microsecondInOneSecond = 1000000;

public:
    void controller(uint8_t _sensor0, const char *_topic, const char *_name, uint64_t _delayTime)
    {
        delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
        uint8_t sensorStatus0 = digitalRead(_sensor0);
        if (sensorStatus0 == 1)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                Serial.print(_sensor0);
                Serial.print(" Status: ");
                Serial.print(sensorStatus0);
                Serial.print("\n");
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
        if (sensorStatus0 == 0 && deviceON)
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
                Serial.print(_sensor0);
                Serial.print(" Status: ");
                Serial.print(sensorStatus0);
                Serial.print("\n");
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
    void controller(uint8_t _sensor0, uint8_t _sensor1, const char *_topic, const char *_name, uint64_t _delayTime)
    {
        delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
        uint8_t sensorStatus0 = digitalRead(_sensor0);
        uint8_t sensorStatus1 = digitalRead(_sensor1);
        if (sensorStatus0 == 1 || sensorStatus1 == 1)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                Serial.print(_sensor0);
                Serial.print(" Status: ");
                Serial.print(sensorStatus0);
                Serial.print("\n");
                Serial.print(_sensor1);
                Serial.print(" Status: ");
                Serial.print(sensorStatus1);
                Serial.print("\n");
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
        if (sensorStatus0 == 0 && sensorStatus1 == 0 && deviceON)
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
                Serial.print(_sensor0);
                Serial.print(" Status: ");
                Serial.print(sensorStatus0);
                Serial.print("\n");
                Serial.print(_sensor1);
                Serial.print(" Status: ");
                Serial.print(sensorStatus1);
                Serial.print("\n");
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
};
SmartOffice c[5];
void setup()
{
    Serial.begin(115200);
    pinMode(sensor0_washRoom1, INPUT);
    pinMode(sensor1_washRoom1, INPUT);
    pinMode(sensor2_washRoom1, INPUT);
    pinMode(sensor3_washRoom1, INPUT);
    pinMode(sensor0_mainRoom, INPUT);
    pinMode(sensor1_mainRoom, INPUT);
    pinMode(sensor2_mainRoom, INPUT);
    pinMode(2, OUTPUT);
    Serial.print("\nCalibrating Sensor: ");
    for (int i = 0; i < 30; i++)
    {
        digitalWrite(2, HIGH);
        Serial.print(".");
        delay(500);
        digitalWrite(2, LOW);
        delay(500);
    }
    Serial.print("\nConnecting to ");
    Serial.print(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    delay(2000);
    Serial.println("\nWiFi connected\nIP address: ");
    Serial.println(WiFi.localIP());
    client.setServer(mqtt_server, mqtt_port);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
    smartOfficeController();
    delay(20);
}
void smartOfficeController()
{
    c[0].controller(sensor0_washRoom1, sensor1_washRoom1, "DS/D0", "4TF_WRL", 1);
    c[1].controller(sensor1_washRoom1, "DS/D1", "4TF_WRE", 2);
    c[2].controller(sensor0_mainRoom, "DS/D2", "4TF_MRL0", 1);
    c[3].controller(sensor1_mainRoom, "DS/D3", "4TF_MRL1", 1);
    // c[4].controller(sensor2_mainRoom, "DS/D4", "4TF_MRL2", 1);
}
