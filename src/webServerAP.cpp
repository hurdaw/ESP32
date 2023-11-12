#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
String HTMLGui(uint8_t led);
const char *ssid = "FPT Lau 1";
const char *pass = "@33ngoquyen";

// IPAddress local_ip(192, 168, 1, 25);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

uint8_t ledPin = 2;
bool ledStatus = LOW;
void event_Onconnect()
{
    ledStatus = LOW;
    Serial.println("Connected ");
    server.send(200, "text/html", HTMLGui(ledStatus));
}
void event_ledOn()
{
    ledStatus = HIGH;
    Serial.println("ledPin is on");
    server.send(200, "text/html", HTMLGui(ledStatus));
}
void event_ledOff()
{
    ledStatus = LOW;
    Serial.println("ledPin is off");
    server.send(200, "text/html", HTMLGui(ledStatus));
}
void event_NotFound()
{
    server.send(400, "text/html", "Not Found");
}
void setup()
{
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status()!=WL_CONNECTED)
    {
        delay(100);
        Serial.println(".");
    }
    Serial.println("Connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    delay(100);
    server.begin();
    Serial.println("Server is starting ");
    server.on("/", event_Onconnect);
    server.on("/ledOn", event_ledOn);
    server.on("/ledOff", event_ledOff);
    server.onNotFound(event_NotFound);
}

void loop()
{
    server.handleClient();
    if (ledStatus)
    {
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }
}
String HTMLGui(uint8_t led)
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
    str += "p {font-size: 20px;color: #4807ed;margin-bottom: 10px;}\n";
    str += "</style>\n";
    str += "</head>\n";
    str += "<body>\n";
    str += "<div class=\"container\">\n";
    str += "<h1>ESP32 WebServer</h1>";

    if (led)
    {
        str += "<p>Led Status: ON</p><a class=\"button button-off\" href=\"/ledOff\">OFF</a>\n";
    }
    else
    {
        str += "<p>Led Status: OFF</p><a class=\"button button-off\" href=\"/ledOn\">ON</a>\n";
    }

    str += "</div>\n";
    str += "</body>\n";
    str += "</html>\n";
    return str;
}
