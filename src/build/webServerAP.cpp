#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
String HTMLGui(uint8_t led, uint8_t led1);
const char *ssid = "FPT Lau 1";
const char *pass = "@33ngoquyen";

// IPAddress local_ip(192, 168, 1, 25);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

uint8_t ledPinR = 23;
uint8_t ledPinG = 15;
bool ledStatusR = LOW;
bool ledStatusG = LOW;
void event_Onconnect()
{

    ledStatusR = LOW;
    ledStatusG = LOW;
    Serial.println("Connected ");
    server.send(200, "text/html", HTMLGui(ledStatusR, ledStatusG));
}
void event_ledOnR()
{
    ledStatusR = HIGH;
    Serial.println("led Red is on");
    server.send(200, "text/html", HTMLGui(true, ledStatusG));
}
void event_ledOffR()
{
    ledStatusR = LOW;
    Serial.println("led Red is off");
    server.send(200, "text/html", HTMLGui(false, ledStatusG));
}
void event_ledOnG()
{
    ledStatusG = HIGH;
    Serial.println("led Green is on");
    server.send(200, "text/html", HTMLGui(ledStatusR, true));
}
void event_ledOffG()
{
    ledStatusG = LOW;
    Serial.println("led Green is off");
    server.send(200, "text/html", HTMLGui(ledStatusR, false));
}
void event_NotFound()
{
    server.send(400, "text/html", "Not Found");
}
void setup()
{
    Serial.begin(115200);
    pinMode(ledPinR, OUTPUT);
    pinMode(ledPinG, OUTPUT);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    delay(100);
    server.begin();
    Serial.println("Server is starting ");
    server.on("/", event_Onconnect);
    server.on("/ledRedOn", event_ledOnR);
    server.on("/ledRedOff", event_ledOffR);
    server.on("/ledGreenOn", event_ledOnG);
    server.on("/ledGreenOff", event_ledOffG);
    server.onNotFound(event_NotFound);
}

void loop()
{
    server.handleClient();
    if(ledStatusR){
        digitalWrite(ledPinR, HIGH);
        delay(100);
        digitalWrite(ledPinR, LOW);
        delay(100);
    }else{
        digitalWrite(ledPinR, LOW);
    }
    if(ledStatusG){
        digitalWrite(ledPinG, HIGH);
        delay(100);
        digitalWrite(ledPinG, LOW);
        delay(100);
    }else{
        digitalWrite(ledPinG, LOW);
    }
}
String HTMLGui(uint8_t ledR, uint8_t ledG)
{
    String str = "<!DOCTYPE html> <html lang=\"en\">\n";
    str += "<head> <meta charset =\"UTF-8\" />\n";
    str += "<title>LED Control</title>\n";
    str += "<style>html {font-family: Arial, Helvetica, sans-serif;margin: 0px auto; text-align: center;}\n";
    str += ".container {background-color: #32a86b;width: 300px;border-radius: 10px;margin: auto;padding: 10px;}\n";
    str += "body {margin-top: 50px;}\n";
    str += "h1 { color: white;margin: 50px 30px;}\n";
    str += ".button {display: block;width: 80px;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    str += ".button-off {background-color: #cc4b4b;}\n";
    str += ".button-off:active {background-color: black;}\n";
    str += ".button-on {background-color: #cc4b4b;}\n";
    str += ".button-on:active {background-color: black;}\n";
    str += ".button-blink {background-color: #cc4b4b;}\n";
    str += ".button-blink:active {background-color: black;}\n";
    str += ".button-blinkOff {background-color: #cc4b4b;}.button-blinkOff:active {background-color: black;}\n";
    str += "p {font-size: 20px;color: #4807ed;margin-bottom: 10px;}\n";
    str += "</style>\n";
    str += "</head>\n";
    str += "<body>\n";
    str += "<div class=\"container\">\n";
    str += "<h1>ESP32 WebServer</h1>";
        if (ledR)
        {
            str += "<p>Led Red Status: ON</p><a class=\"button button-off\" href=\"/ledRedOff\">OFF</a>\n";
        }
        else
        {
            str += "<p>Led Red Status: OFF</p><a class=\"button button-off\" href=\"/ledRedOn\">ON</a>\n";
        }
        if (ledG)
        {
            str += "<p>Led Green Status: ON</p><a class=\"button button-off\" href=\"/ledGreenOff\">OFF</a>\n";
        }
        else
        {
            str += "<p>Led Green Status: OFF</p><a class=\"button button-off\" href=\"/ledGreenOn\">ON</a>\n";
        }

    str += "</div>\n";
    str += "</body>\n";
    str += "</html>\n";
    return str;
}
