/*
  Library for ESP32
*/
#ifndef Drops_h
#define Drops_h
 
#include "Arduino.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIoClient.h>
 
class Drops
{
  public:
    Drops(String _url, String _id, String _idProject);
    void serverConnection();
    void loop();
    void sendData(String nameDrop,bool state);
    void sendData(String nameDrop,int value);
    void sendData(String nameDrop,float value);
    void sendData(String nameDrop,double value);
    void sendData(String nameDrop,int *value, int sizeData);
    void sendData(String nameDrop,float *value, int sizeData);
    void sendData(String nameDrop,double *value, int sizeData);
    void sendData(String nameDrop,char *text);
    void wifiConnection(String ssid, String pass);

    void (*fp)(String nameButton, bool stateButton);
  private:
    String url;
    String id;
    String idProject;
    WiFiClient  client;
    SocketIoClient socketIO;
    StaticJsonDocument<2000> docJson;
    //= jsonBufferAux.createObject();
    String jsonString;
    void eventWrite(const char * payload, size_t length);
    void connectFunction(const char * payload, size_t length);
 
};
 
#endif