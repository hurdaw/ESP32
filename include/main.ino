#include <Arduino.h>
#include <WiFi.h>
const char *ssid = "alo";
const char *pass = "abc";

int led = 2;
void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.begin(ssid, pass);
  pinMode(led, OUTPUT);
}

void loop()
{
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(100);
}
