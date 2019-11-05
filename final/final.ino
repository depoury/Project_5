#include <Stepper.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>

uint8_t step1 = 32;
uint8_t step2 = 33;
uint8_t step3 = 25;
uint8_t step4 = 26;
uint8_t servo1 = 13;

Stepper stepper = Stepper(2038, step1, step2, step3, step4);
Servo servo;

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);
WiFiUDP udp;

int pos = 0;
int k = 1;
bool STOP = false;

void setup() {
  Serial.begin(115200);
  pinMode(step1, OUTPUT);
  pinMode(step2, OUTPUT);
  pinMode(step3, OUTPUT);
  pinMode(step4, OUTPUT);
  pinMode(servo1, OUTPUT);
  stepper.setSpeed(6);
  servo.attach(servo1);
  servo.write(0);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  server.begin();
  udp.begin(57222);
  delay(500);
}

void loop() {
  if (!STOP) {
    stepper.step(340);
    if (pos == 180) {
      k = -1;
    } else if (pos == 0) {
      k = 1;
    }
    pos += k * 5;
    servo.write(pos);
  }
  checkDead();
}

bool checkDead() {
  uint8_t buffer[50] = "";
  memset(buffer, 0, 50);
  udp.parsePacket();
  String tmp;
  if(udp.read(buffer, 50) > 0){
    //Serial.println((char *)buffer);
    tmp = String((char *) buffer);
    Serial.println(tmp);
    if (tmp.startsWith("Stop!")) {
      Serial.println("CMD: STOP");
      STOP = true;
      delay(1000);
    } else if (tmp.startsWith("Start!")) {
      Serial.println("CMD: START");
      STOP = false;
    } else {
      Serial.println("UNKNOWN COMMAND!");
    }
  }
}
