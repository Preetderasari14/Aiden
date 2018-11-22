#include <ESP8266WiFi.h>
const char* ssid = "raspi";
const char* password = "qwerty17";
const char* host = "dweet.io";
#include<Wire.h>
const int MPU2=0x69,MPU1=0x68;
int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2;
void setup() {
Wire.begin();
Serial.begin(38400);
Wire.beginTransmission(MPU1);
Wire.write(0x6B);// PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);Wire.begin();
Wire.beginTransmission(MPU2);
Wire.write(0x6B);// PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);
// We start by connecting to a WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
//ESP.wdtFeed();
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void GetMpuValue1(const int MPU){
Wire.beginTransmission(MPU);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
AcX1=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
AcY1=Wire.read()<<8| Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
AcZ1=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
Tmp1=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
GyX1=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
GyY1=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
GyZ1=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
Serial.print("AcX = ");
Serial.print(AcX1);
Serial.print(" | AcY = ");
Serial.print(AcY1);
Serial.print(" | AcZ = ");
Serial.print(AcZ1);
Serial.print(" | GyX = ");
Serial.print(GyX1);
Serial.print(" | GyY = ");
Serial.print(GyY1);
Serial.print(" | GyZ = ");
Serial.println(GyZ1);
Serial.print("connecting to ");
Serial.println(host);
// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}
// This will send the request to the server
client.print(String("GET /dweet/for/cute-bubble?AcX=") + AcX1 + "&AcY="+AcY1+ "&AcZ="+AcZ1+ "&GyX="+GyX1+ "&GyY="+GyY1+
"&GyZ="+GyZ1+ "&Tmp="+Tmp1+ " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
delay(10);
// Read all the lines of the reply from server and print them to Serial
while(client.available()){
String line = client.readStringUntil('\r');
Serial.print(line);
}
Serial.println();
Serial.println("closing connection");
}
void GetMpuValue2(const int MPU){
Wire.beginTransmission(MPU);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
AcX2=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
AcY2=Wire.read()<<8| Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
AcZ2=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
Tmp2=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
GyX2=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
GyY2=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
GyZ2=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
Serial.print("AcX = ");
Serial.print(AcX2);
Serial.print(" | AcY = ");
Serial.print(AcY2);
Serial.print(" | AcZ = ");
Serial.print(AcZ2);
Serial.print(" | GyX = ");
Serial.print(GyX2);
Serial.print(" | GyY = ");
Serial.print(GyY2);
Serial.print(" | GyZ = ");
Serial.println(GyZ2);
Serial.print("connecting to ");
Serial.println(host);
// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}
// This will send the request to the server
client.print(String("GET /dweet/for/cute-bubble?AcX=") + AcX2 + "&AcY="+AcY2+ "&AcZ="+AcZ2+ "&GyX="+GyX2+ "&GyY="+GyY2+
"&GyZ="+GyZ2+ "&Tmp="+Tmp2+ " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
delay(10);
// Read all the lines of the reply from server and print them to Serial
while(client.available()){
String line = client.readStringUntil('\r');
Serial.print(line);
}
Serial.println();
Serial.println("closing connection");
}
void loop() {
//get values for first mpu having address of 0x68
GetMpuValue1(MPU1);
Serial.print(" ");
Serial.print("|||");
//get values for second mpu having address of 0x69
GetMpuValue2(MPU2);
Serial.println("");}
