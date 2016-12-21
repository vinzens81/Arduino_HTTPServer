
/*
  HTTP Server Lib to provide OOP based http Packet handling
  By Joeran vinzens
*/

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>

#include "HTTPServer.h"
String _variable;
String _httpMethod;
String _httpPath;
String _clientHostIP;
String _contentType;
String _content;
int _contentLength;
int _contentLengthRemaining;
EthernetClient _clientConnection;

HTTPServer::HTTPServer(EthernetClient clientConnection)
{
  _clientConnection = clientConnection; 
  _variable = "";
  _httpMethod = "";
  _httpPath = "";
  _clientHostIP = "";
  _contentType = "";
  _content = "";
  _contentLength = 0;
  _contentLengthRemaining = 0;
  String _line = "";
  char _c;
  boolean _end = false;

  while (_clientConnection.connected()) {
    if (_clientConnection.available()) {
      _c = _clientConnection.read();
    }
    _line = _line + String(_c);
    if (_c == '\n') {
      if (_line == "\r\n") {
        _end = true;
        _contentLengthRemaining = _contentLength;
      } else {
        _processLine(_line);
      }
      _line = "";
    } else if ( _contentLengthRemaining > 0 ) {
      _contentLengthRemaining = _contentLengthRemaining - 1;
    }
    if ( _contentLength > 0 and _contentLengthRemaining == 0 and _end == true) {
      _content = _line;
      break;
    }
  }
  return;
}

/*
Private Methods
*/
void HTTPServer::_processLine(String _line) {
  _line.trim();
  if
   ( _line.startsWith("GET ")) 
  {
    _httpMethod = "GET";
    _httpPath = _line.substring(4);
    _httpPath.remove(_httpPath.length()-8);
    return;
  }
  else if 
   ( _line.startsWith("PUT ")) 
  {
    _httpMethod = "PUT";
    _httpPath = _line.substring(4);
    _httpPath.remove(_httpPath.length()-8);
    return;
  }
  else if 
   ( _line.startsWith("Host: ")) 
  {
    _clientHostIP = _line.substring(6);
    return;
  }
  else if 
   ( _line.startsWith("Content-Length: ")) 
  {
    _contentLength = _line.substring(16).toInt();
    return;
  }
  else if 
   ( _line.startsWith("Content-Type: ")) 
  {
    _contentType = _line.substring(14);
    return;
  }

}



/*
Begin of Public Methods
*/

String HTTPServer::getRequestType() {
  return(_httpMethod);
}
String HTTPServer::getClientHostIP() {
  return(_clientHostIP);
}
String HTTPServer::getPath() {
  return(_httpPath);
}
String HTTPServer::getContentType() {
  return(_contentType);
}
String HTTPServer::getContent() {
  return(_content);
}
int HTTPServer::getContentLength() {
  return(_contentLength);
}
boolean HTTPServer::closeConnection() {
  _clientConnection.stop();
  return true;
}
boolean HTTPServer::send200OK(String message) {
  _clientConnection.println("HTTP/1.1 200 OK");
  _clientConnection.println("Connection: close");  // the connection will be closed after completion of the response
  _clientConnection.println("Content-Type: text/html");
  _clientConnection.println();
  _clientConnection.println("<!DOCTYPE HTML>");
  _clientConnection.print("<html><p>");
  _clientConnection.print(message);
  _clientConnection.println("</p></html>");
  delay(1);
  return true;
}

