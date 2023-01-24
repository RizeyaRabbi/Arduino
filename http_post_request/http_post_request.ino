#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <StreamUtils.h>
byte mac[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
IPAddress ip(192, 168, 0, 32);
IPAddress server(192, 168, 0, 89);  // server address
int port = 80;
EthernetClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  Serial.print("Initializing Ethernet:");
  Serial.print(" ");
  for (int i = 0; i < 5; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\n");
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.print("Ethernet shield was not found.");
  } else if (Ethernet.hardwareStatus() == EthernetW5100) {
    Serial.print("W5100 Ethernet controller detected.");
  }
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
  delay(5000);
  unsigned long startTime = millis();
  //httpPost("13oct10am", 10);
  //httpPUT("22101000000044", "0");
  //String a = httpPostGet("22101000000044");
  String a = httpGet("22101000000044");
  Serial.print("\n");
   Serial.print("Status: ");
  Serial.print(a);
  Serial.print("\n");
  Serial.print("Time: ");
  Serial.print(millis() - startTime);
  Serial.print("\n");
}

void loop() {
}
void httpPost(String name, int time) {
  StaticJsonDocument<48> doc;
  doc["IOT_NAME"] = name;
  doc["TIME_ON"] = time;
  //String postData;
  //serializeJson(doc, postData);
  WriteBufferingStream bufferedClient(client, 64);
  if (client.connect(server, port)) {
    client.println("POST /ati-erp/api/create-iot-log HTTP/1.1");
    client.println("Host: 192.168.0.89");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(measureJson(doc));
    client.println("Content-Type: application/json");
    client.println();
    //client.println(postData);
    serializeJson(doc, bufferedClient);
    //bufferedClient.flush();
  }
  // Check HTTP status
  //char status[32] = { 0 };
  //client.readBytesUntil('\r', status, sizeof(status));
  // Serial.println(status);
}

void httpPUT(String id, String status) {
  StaticJsonDocument<48> doc;
  doc["DEVICE_ID"] = id;
  doc["STATUS"] = status;
  WriteBufferingStream bufferedClient(client, 64);
  if (client.connect(server, port)) {
    client.println("PUT /ati-erp/api/update-iot-device HTTP/1.1");
    client.println("Host: 192.168.0.89");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(measureJson(doc));
    client.println("Content-Type: application/json");
    client.println();
    serializeJson(doc, bufferedClient);
  }
}

String httpPostGet(String id) {
  StaticJsonDocument<48> doc;
  doc["DEVICE_ID"] = id;
  String postData;
  serializeJson(doc, postData);
  if (client.connect(server, port)) {
    client.println("POST /ati-erp/api/get-iot-device-status HTTP/1.1");
    client.println("Host: 192.168.0.89");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println("Content-Type: application/json");
    client.println();
    client.println(postData);
    //delay(1);
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      client.stop();
      return;
    }
    StaticJsonDocument<128> doc;
    ReadBufferingStream bufferedFile(client, 64);
    DeserializationError error = deserializeJson(doc, bufferedFile);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    //JsonObject root_0 = doc[0];
    //bool success = doc["success"];                         // true
    //int status = doc["status"];                            // 200
    //const char* message = doc["message"];                  // "Data Get Successfully"
    const char* iotDeviceStatus = doc["iotDeviceStatus"];  // "1"
    //Serial.println(iotDeviceStatus);
    //int deviceStatus = atoi(iotDeviceStatus);
    return iotDeviceStatus;
  } else {
    Serial.println(".....connection failed....");
  }
  client.stop();
}

String httpGet(String id) {
  StaticJsonDocument<48> doc;
  doc["DEVICE_ID"] = id;
  String postData;
  serializeJson(doc, postData);
  if (client.connect(server, port)) {
    client.println("GET /ati-erp/api/get-iot-device-status HTTP/1.1");
    client.println("Host: 192.168.0.89");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
   client.println(postData.length());
    client.println("Content-Type: application/json");
    client.println();
    client.println(postData);
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
      Serial.println(F("Invalid response"));
      client.stop();
      return;
    }
    StaticJsonDocument<32> doc;
    ReadBufferingStream bufferedFile(client, 64);
    DeserializationError error = deserializeJson(doc, bufferedFile);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    const char* status = doc["status"];  // "0"
    return status;
  }
}