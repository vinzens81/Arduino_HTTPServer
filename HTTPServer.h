
/*
  HTTP Server Lib to provide OOP based http Packet handling
  By Joeran vinzens
*/


#ifndef HTTPServer_h
#define HTTPServer_h

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>

class HTTPServer
{
  public:

    HTTPServer(EthernetClient clientConnection);
    String getRequestType();
    String getClientHostIP();
    String getPath();
    String getContentType();
    String getContent();
    int getContentLength();
    boolean send200OK(String message);
    boolean closeConnection();
  private:
    String _variable;
    String _httpMethod;
    String _httpPath;
    String _clientHostIP;
    String _contentType;
    String _content;
    String _line;
    char _c;
    int _contentLength;
    boolean _end;
    void _processLine(String line);
    EthernetClient _clientConnection;
};
#endif

