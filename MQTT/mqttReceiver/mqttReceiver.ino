// Define logic level.
#define ON HIGH
#define OFF LOW

// Define Libraries.
#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>

// MQTT server credentils.
const char *mqtt_server = "91.121.93.94";
const char *mqtt_username = "";
const char *mqtt_password = "";
const int mqtt_port = 1883;

// OUTPUT device declaration with PIN number.
const byte washRoom_Light_4thFloor = 22, washRoom_Exhaust_4thFloor = 23;
const byte mainRoom_Light_0 = 24, mainRoom_Light_1 = 25, mainRoom_Light_2 = 26;

// Ethernet connection credentials.
byte mac[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFE};
IPAddress ip(192, 168, 0, 118);
EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect()
{
    // Loop until we’re reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection…");
        String clientId = "A-"; // random client ID
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password))
        {
            Serial.println("connected");
            client.subscribe("DS/4TF_WRL");
            client.subscribe("DS/4TF_WRE");
            client.subscribe("DS/4TF_MRL0");
            client.subscribe("DS/4TF_MRL1");
            client.subscribe("DS/4TF_MRL2");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String incommingMessage;
    for (int i = 0; i < length; i++)
    {
        incommingMessage += (char)payload[i];
    }
    if (strcmp(topic, "DS/4TF_WRL") == 0)
    {
        if (incommingMessage.equals("1"))
        {
            byte pinStatus = digitalRead(washRoom_Light_4thFloor);
            if (pinStatus == OFF)
            {
                digitalWrite(washRoom_Light_4thFloor, ON);
            }
        }
        if (incommingMessage.equals("0"))
        {
            byte pinStatus = digitalRead(washRoom_Light_4thFloor);
            if (pinStatus == ON)
            {
                digitalWrite(washRoom_Light_4thFloor, OFF);
            }
        }
    }

    if (strcmp(topic, "DS/4TF_WRE") == 0)
    {
        if (incommingMessage.equals("1"))
        {
            digitalWrite(washRoom_Exhaust_4thFloor, ON);
        }
        else
        {
            digitalWrite(washRoom_Exhaust_4thFloor, OFF);
        }
    }

    if (strcmp(topic, "DS/4TF_MRL0") == 0)
    {
        if (incommingMessage.equals("1"))
        {
            digitalWrite(mainRoom_Light_0, ON);
        }
        else
        {
            digitalWrite(mainRoom_Light_0, OFF);
        }
    }

    if (strcmp(topic, "DS/4TF_MRL1") == 0)
    {
        if (incommingMessage.equals("1"))
        {
            digitalWrite(mainRoom_Light_1, ON);
        }
        else
        {
            digitalWrite(mainRoom_Light_1, OFF);
        }
    }

    if (strcmp(topic, "DS/4TF_MRL2") == 0)
    {
        if (incommingMessage.equals("1"))
        {
            digitalWrite(mainRoom_Light_2, ON);
        }
        else
        {
            digitalWrite(mainRoom_Light_2, OFF);
        }
    }
}

void setup()
{
    digitalWrite(washRoom_Light_4thFloor, OFF);
    digitalWrite(washRoom_Exhaust_4thFloor, OFF);
    digitalWrite(mainRoom_Light_0, OFF);
    digitalWrite(mainRoom_Light_1, OFF);
    digitalWrite(mainRoom_Light_2, OFF);
    Serial.begin(9600);

    pinMode(washRoom_Light_4thFloor, OUTPUT);
    pinMode(washRoom_Exhaust_4thFloor, OUTPUT);
    pinMode(mainRoom_Light_0, OUTPUT);
    pinMode(mainRoom_Light_1, OUTPUT);
    pinMode(mainRoom_Light_2, OUTPUT);

    Ethernet.begin(mac, ip);
    delay(1000);
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
}
void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}