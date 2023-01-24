// Must be changed according to Relay logic.
#define on HIGH
#define off LOW

// Libraries Needed for the project.
#include <StreamUtils.h>
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

// Necessaery Variable declaration for Ethernet connection.
byte mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFE};
IPAddress ip(192, 168, 0, 118);
IPAddress server(192, 168, 0, 89);
EthernetClient client;
byte port = 80;

// Class that performs arithmatic and logical calculations.
class SmartOffice
{
private:
    boolean motion = false, deviceON = false, delayRunning = false, logFlag = false;
    unsigned long startDelay, startInterval, timeOn, logStart, logStop, logValue;

public:
    void controller(byte _sensor0, byte _device, const char *_name, unsigned long _delayTime)
    {
        byte sensorStatus0 = digitalRead(_sensor0);
        if (sensorStatus0 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
                delay(20);
                if (!logFlag)
                {
                    logStart = millis();
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
                startDelay = millis();
                delayRunning = true;
            }
        }
        if (!motion && (millis() - startDelay >= _delayTime))
        {
            if (deviceON)
            {
                deviceON = false;
                delayRunning = false;
                digitalWrite(_device, off);
                delay(20);
                if (logFlag)
                {
                    logStop = millis();
                    logValue = (logStop - logStart) / 1000UL;
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

    void controller(byte _sensor0, byte _sensor1, byte _device, const char *_name, unsigned long _delayTime)
    {
        byte sensorStatus0 = digitalRead(_sensor0);
        byte sensorStatus1 = digitalRead(_sensor1);
        if (sensorStatus0 == HIGH || sensorStatus1 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
                delay(20);
                if (!logFlag)
                {
                    logStart = millis();
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
                startDelay = millis();
                delayRunning = true;
            }
        }
        if (!motion && (millis() - startDelay >= _delayTime))
        {
            if (deviceON)
            {
                deviceON = false;
                delayRunning = false;
                digitalWrite(_device, off);
                delay(20);
                if (logFlag)
                {
                    logStop = millis();
                    logValue = (logStop - logStart) / 1000UL;
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

    void controller(byte _sensor0, byte _sensor1, byte _sensor2, byte _device, const char *_name, unsigned long _delayTime)
    {
        byte sensorStatus0 = digitalRead(_sensor0);
        byte sensorStatus1 = digitalRead(_sensor1);
        byte sensorStatus2 = digitalRead(_sensor2);
        if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
                delay(20);
                if (!logFlag)
                {
                    logStart = millis();
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
                startDelay = millis();
                delayRunning = true;
            }
        }
        if (!motion && (millis() - startDelay >= _delayTime))
        {
            if (deviceON)
            {
                deviceON = false;
                delayRunning = false;
                digitalWrite(_device, off);
                delay(20);
                if (logFlag)
                {
                    logStop = millis();
                    logValue = (logStop - logStart) / 1000UL;
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

    void controller(byte _sensor0, byte _sensor1, byte _sensor2, byte _sensor3, byte _device, const char *_name, unsigned long _delayTime)
    {
        byte sensorStatus0 = digitalRead(_sensor0);
        byte sensorStatus1 = digitalRead(_sensor1);
        byte sensorStatus2 = digitalRead(_sensor2);
        byte sensorStatus3 = digitalRead(_sensor3);
        if (sensorStatus0 == HIGH || sensorStatus1 == HIGH || sensorStatus2 == HIGH || sensorStatus3 == HIGH)
        {
            motion = true;
            if (!deviceON)
            {
                deviceON = true;
                digitalWrite(_device, on);
                delay(20);
                if (!logFlag)
                {
                    logStart = millis();
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
                startDelay = millis();
                delayRunning = true;
            }
        }
        if (!motion && (millis() - startDelay >= _delayTime))
        {
            if (deviceON)
            {
                deviceON = false;
                delayRunning = false;
                digitalWrite(_device, off);
                delay(20);
                if (logFlag)
                {
                    logStop = millis();
                    logValue = (logStop - logStart) / 1000UL;
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
    void interval(unsigned long intervalTime, void (&function)())
    {
        if (millis() - startInterval >= intervalTime)
        {
            function();
            startInterval = millis();
        }
    }
    void writeLog(const char *_deviceName, unsigned int _timeOn)
    {
        StaticJsonDocument<48> doc;
        doc["IOT_NAME"] = _deviceName;
        doc["TIME_ON"] = _timeOn;
        WriteBufferingStream bufferedClient(client, 64);
        if (client.connect(server, port))
        {
            client.println("POST /ati-erp/api/create-iot-log HTTP/1.1");
            client.println("Host: 192.168.0.89");
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

// Object of the class
SmartOffice smartOffice[5];

// INPUT type variables with Pin number.
const byte sensor0_washRoom1 = A15, sensor1_washRoom1 = A14, sensor2_washRoom1 = A13, sensor3_washRoom1 = A12,
           sensor0_mainRoom = A11, sensor1_mainRoom = A10, sensor2_mainRoom = A9;

// OUTPUT type variables with Pin number.
const byte light_washRoom1 = 22, exhaust_washRoom1 = 23,
           light0_mainRoom = 24, light1_mainRoom = 25, light2_mainRoom = 26;

// Pin configuration & Ethernet connection.
void setup()
{
    for (byte i = 22; i <= 26; i++)
    {
        digitalWrite(i, off);
    }

    Serial.begin(9600);

    pinMode(light_washRoom1, OUTPUT);
    pinMode(exhaust_washRoom1, OUTPUT);
    pinMode(light0_mainRoom, OUTPUT);
    pinMode(light1_mainRoom, OUTPUT);
    pinMode(light2_mainRoom, OUTPUT);

    pinMode(sensor0_washRoom1, INPUT_PULLUP);
    pinMode(sensor1_washRoom1, INPUT_PULLUP);
    pinMode(sensor2_washRoom1, INPUT_PULLUP);
    pinMode(sensor3_washRoom1, INPUT_PULLUP);
    pinMode(sensor0_mainRoom, INPUT_PULLUP);
    pinMode(sensor1_mainRoom, INPUT_PULLUP);
    pinMode(sensor2_mainRoom, INPUT_PULLUP);

    Ethernet.begin(mac, ip);
    Serial.print("Initializing Ethernet: ");
    for (int i = 0; i < 2; i++)
    {
        Serial.print(".");
        delay(1000);
    }
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.print("\n");
        Serial.print("Ethernet shield was not found.");
    }
    else if (Ethernet.hardwareStatus() == EthernetW5100)
    {
        Serial.print("\n");
        Serial.print("W5100 Ethernet controller detected.");
        Serial.print("\n");
        Serial.print("IP address:");
        Serial.print(" ");
        Serial.print(Ethernet.localIP());
        Serial.print("\n");
        Serial.print("Subnet mask:");
        Serial.print(" ");
        Serial.print(Ethernet.subnetMask());
        Serial.print("\n");
        Serial.print("Ethernet Ready");
        Serial.print("\n");
    }
}

// Function that runs forever.
void loop()
{
    smartOffice[0].interval(300, LightController);
    smartOffice[1].interval(800, ExhaustController);
}

// Helper Functions.
void LightController()
{
    smartOffice[0].controller(sensor0_washRoom1, sensor1_washRoom1, sensor2_washRoom1, sensor3_washRoom1,
                              light_washRoom1, "4F_WR1_LIGHT", 2000UL);
    smartOffice[2].controller(sensor0_mainRoom, light0_mainRoom, "4F_MR_LIGHT0", 3000);
    smartOffice[3].controller(sensor1_mainRoom, light1_mainRoom, "4F_MR_LIGHT1", 4000);
    smartOffice[4].controller(sensor2_mainRoom, light2_mainRoom, "4F_MR_LIGHT2", 5000);
}
void ExhaustController()
{
    smartOffice[1].controller(sensor2_washRoom1, sensor3_washRoom1, exhaust_washRoom1, "4F_WR1_EXHAUST", 6000UL);
}