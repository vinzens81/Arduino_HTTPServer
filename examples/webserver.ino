#include <ArduinoJson.h>

#include <SPI.h>
#include <Ethernet.h>
#include <HTTPServer.h>


String path = "";
int contentLength = 0;
String content = "";
String method = "";

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 1);
byte subnet[] = { 255, 255, 255, 0 };
byte gateway[] = { 192, 168, 0, 255 };
EthernetServer server(80);
void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}
void loop()
{
  path = "";
  contentLength = 0;
  content = "";
  method = "";
  EthernetClient client = server.available();
  if (client) {
    HTTPServer HTTPServer(client);
    path = HTTPServer.getPath();
    contentLength = HTTPServer.getContentLength();
    content = HTTPServer.getContent();
    method = HTTPServer.getRequestType();
    if ( HTTPServer.send200OK("Thanks") == true ) {
      Serial.println("Answer send");
    }
    if ( HTTPServer.closeConnection() == true ) {
      Serial.println("Connection Closed");
    }
  }
  Serial.println(method);
  Serial.println(path);
  Serial.println(content);
}

