// Must be changed according to Relay logic.
#define on LOW
#define off HIGH
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Libraries Needed for the project.
#include <WiFi.h>
#include <PubSubClient.h>
#include "freertos/timers.h"
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include <WiFi.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

char ssid[] = "Esp32Test";
char password[] = "1234567890";

// const char ssid[] = "atilimited.net2"; // WiFi SSID
// const char password[] = "AtiL2@2021#"; // WIFi Password
// IPAddress server(203, 130, 133, 166);
const char server[] = "203.130.133.166"; // Server Address
uint8_t port = 80;                       // Server port
WiFiClient client;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Class that performs arithmatic and logical calculations for this project.
class SmartOffice
{
private:
    bool motion = false, deviceON = false, delayRunning = false, logFlag = false;
    uint64_t startDelay, delayTime, startInterval, timeOn, logStart, logStop, logValue,
        intervalTime, secondInOneMinute = 60, microsecondInOneSecond = 1000000;

public:
    // Takes 1 Sensor pin,device pin,device name, delay time as input.
    // Activates device according to Sensor status and writes Log for how much time the device was ON.
    void controller(uint8_t _sensor0, uint8_t _device, const char *_name, uint64_t _delayTime)
    {
        delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
        uint8_t sensorStatus0 = digitalRead(_sensor0);
        if (sensorStatus0 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
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
                digitalWrite(_device, off);
                if (logFlag)
                {
                    logStop = esp_timer_get_time();
                    logValue = (logStop - logStart) / 1000000UL;
                    writeLog(_name, logValue);
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
    // Takes 2 Sensor pin,device pin,device name, delay time as input.
    // Activates device according to Sensor status and writes Log for how much time the device was ON.
    void controller(uint8_t _sensor0, uint8_t _sensor1, uint8_t _device, const char *_name, uint64_t _delayTime)
    {
        delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
        uint8_t sensorStatus0 = digitalRead(_sensor0);
        uint8_t sensorStatus1 = digitalRead(_sensor1);
        if (sensorStatus0 == HIGH || sensorStatus1 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
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
        if (sensorStatus0 == LOW && sensorStatus1 == LOW && deviceON)
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
                digitalWrite(_device, off);
                if (logFlag)
                {
                    logStop = esp_timer_get_time();
                    logValue = (logStop - logStart) / 1000000UL;
                    writeLog(_name, logValue);
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
    // Takes 3 Sensor pin,device pin,device name, delay time as input.
    // Activates device according to Sensor status and writes Log for how much time the device was ON.
    void controller(uint8_t _sensor0, uint8_t _sensor1, uint8_t _sensor2, uint8_t _device, const char *_name, uint64_t _delayTime)
    {
        delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
        uint8_t sensorStatus0 = digitalRead(_sensor0);
        uint8_t sensorStatus1 = digitalRead(_sensor1);
        uint8_t sensorStatus2 = digitalRead(_sensor2);
        if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
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
        if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW && deviceON)
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
                digitalWrite(_device, off);
                if (logFlag)
                {
                    logStop = esp_timer_get_time();
                    logValue = (logStop - logStart) / 1000000UL;
                    writeLog(_name, logValue);
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
    // Takes 4 Sensor pin,device pin,device name, delay time as input.
    // Activates device according to Sensor status and writes Log for how much time the device was ON.
    void controller(uint8_t _sensor0, uint8_t _sensor1, uint8_t _sensor2, uint8_t _sensor3, uint8_t _device, const char *_name, uint64_t _delayTime)
    {
        delayTime = _delayTime * microsecondInOneSecond * secondInOneMinute;
        uint8_t sensorStatus0 = digitalRead(_sensor0);
        uint8_t sensorStatus1 = digitalRead(_sensor1);
        uint8_t sensorStatus2 = digitalRead(_sensor2);
        uint8_t sensorStatus3 = digitalRead(_sensor3);
        if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH || sensorStatus3 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
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
        if (sensorStatus0 == LOW && sensorStatus1 == LOW && sensorStatus2 == LOW && sensorStatus3 == LOW && deviceON)
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
                digitalWrite(_device, off);
                if (logFlag)
                {
                    logStop = esp_timer_get_time();
                    logValue = (logStop - logStart) / 1000000UL;
                    writeLog(_name, logValue);
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
    // Takes time in Minute and a void function without parameter as INPUT
    //  Calls the funstion every given time
    void interval(uint64_t _intervalTime, void (&function)())
    {
        intervalTime = _intervalTime * microsecondInOneSecond * secondInOneMinute;
        if (esp_timer_get_time() - startInterval >= intervalTime)
        {
            function();
            startInterval = esp_timer_get_time();
        }
    }
    // Writes LOG for how much time the device was ON.
    void writeLog(const char *_deviceName, uint64_t _timeOn)
    {
        StaticJsonDocument<48> doc;
        doc["IOT_NAME"] = _deviceName;
        doc["TIME_ON"] = _timeOn;
        WriteBufferingStream bufferedClient(client, 64);
        if (client.connect(server, port))
        {
            client.println("POST /ATI-ERP2/api/create-iot-log HTTP/1.1");
            client.println("Host: " + String(server));
            client.println("User-Agent: Arduino/1.0");
            client.println("Connection: close");
            client.print("Content-Length: ");
            client.println(measureJson(doc));
            client.println("Content-Type: application/json");
            client.println();
            serializeJson(doc, bufferedClient);
        }
        else
        {
            Serial.println("Can't connect to the server");
        }
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Object of the class SmartOffice
SmartOffice smartOffice[5];
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

// INPUT Variables(Sensor Pin)
const uint8_t
    sensor0_washRoom1 = 23, // D23
    sensor1_washRoom1 = 22, // D22
    sensor2_washRoom1 = 21, // D21
    sensor3_washRoom1 = 19, // D19
    sensor0_mainRoom = 4,   // D4
    sensor1_mainRoom = 16,  // RX2
    sensor2_mainRoom = 17;  // TX2
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// WiFi event functions
void WiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("WiFi Connected");
}
void IP(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
void WiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("WiFi Disconnected.");
    Serial.println("Trying to Reconnect.");
    WiFi.begin(ssid, password);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Pin configuration & WiFi connection.
void setup()
{
    Serial.begin(115200);
    // Sensor INPUT PINS are set to INPUT_PULLUP.
    pinMode(sensor0_washRoom1, INPUT_PULLUP);
    pinMode(sensor1_washRoom1, INPUT_PULLUP);
    pinMode(sensor2_washRoom1, INPUT_PULLUP);
    pinMode(sensor3_washRoom1, INPUT_PULLUP);
    pinMode(sensor0_mainRoom, INPUT_PULLUP);
    pinMode(sensor1_mainRoom, INPUT_PULLUP);
    pinMode(sensor2_mainRoom, INPUT_PULLUP);

    // Automatically reconnects after  connection is lost.
    WiFi.onEvent(WiFiConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(IP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(WiFiDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    WiFi.begin(ssid, password);

    // Sensor Calibrating Time delay(30s)
    Serial.print("\n");
    Serial.print(" Initializing and Calibrating Sensor: ");
    for (uint8_t i = 0; i < 30; i++)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.print(" Ready");
    Serial.print("\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
    smartOffice[0].controller(sensor0_washRoom1, sensor1_washRoom1, sensor2_washRoom1, sensor3_washRoom1,
                              light_washRoom1, "4F_WR1_LIGHT", 3);
    smartOffice[1].controller(sensor2_washRoom1, sensor3_washRoom1, exhaust_washRoom1, "4F_WR1_EXHAUST", 4);
    smartOffice[2].controller(sensor0_mainRoom, light0_mainRoom, "4F_MR_LIGHT0", 2);
    smartOffice[3].controller(sensor1_mainRoom, light1_mainRoom, "4F_MR_LIGHT1", 2);
    smartOffice[4].controller(sensor2_mainRoom, light2_mainRoom, "4F_MR_LIGHT2", 2);
}
