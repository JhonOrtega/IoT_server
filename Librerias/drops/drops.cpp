
/*
  Library for ESP32
*/
 
#include "Arduino.h"
#include "Drops.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <SocketIoClient.h>

// ------------------------------------------------------------ Constructor -----------------------------------------------------------------------------
Drops::Drops(String _url, String _id, String _idProject){
  url = _url;
  id = _id;
  idProject = _idProject; 
}
 
  // --------------------------------------------------------- Functions sendData ----------------------------------------------------------------

// ----------- Function sendData --- bool ---------

void Drops::sendData(String nameDrop,bool state){
  docJson.clear();
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "bool";
  drop["data"] = state;
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);

  socketIO.emit("sendData", output);
}

// ----------- Function sendData --- int ---------

void Drops::sendData(String nameDrop,int value){
  docJson.clear();
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "number";
  drop["data"] = value;
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);
    
  socketIO.emit("sendData", output);
}

// ----------- Function sendData --- float ---------

void Drops::sendData(String nameDrop,float value){
  docJson.clear();
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "number";
  drop["data"] = value;
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);
  
  socketIO.emit("sendData", output);
}

// ----------- Function sendData --- double ---------

void Drops::sendData(String nameDrop,double value){
  docJson.clear();
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "number";
  drop["data"] = value;
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);
  
  socketIO.emit("sendData", output); 
}

// ----------- Function sendData --- int array ---------

void Drops::sendData(String nameDrop,int *value, int sizeData){
  docJson.clear();
  
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "number";
  //drop["data"] = value;
  JsonArray array = drop.createNestedArray("data");
  for(int i=0; i<sizeData; i++){
    array.add(value[i]);
  }
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);
  
  socketIO.emit("sendData", output);
}
// ----------- Function sendData --- float array ---------

void Drops::sendData(String nameDrop,float *value, int sizeData){
  docJson.clear();
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "number";
  //drop["data"] = value;
  JsonArray array = drop.createNestedArray("data");
  for(int i=0; i<sizeData; i++){
    array.add(value[i]);
  }
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);

  socketIO.emit("sendData", output);
}

// ----------- Function sendData --- char ---------

void Drops::sendData(String nameDrop,char *text){
  docJson.clear();
  char nameId[30];
  id.toCharArray(nameId,30);
  docJson["idUser"].set(nameId);
  char nameIdProject[30];
  idProject.toCharArray(nameIdProject,30);
  docJson["idProject"].set(nameIdProject);

  JsonObject drop = docJson.createNestedObject("drop");
  char nameChar[30];
  nameDrop.toCharArray(nameChar,30);
  drop["name"].set(nameChar);
  drop["type"] = "text";
  drop["data"].set(text);
  String output;
  serializeJsonPretty(docJson, output);
  //Serial.print(output);

  socketIO.emit("sendData", output);    
}

// ------------------------------------------------------------- Function serverConnection ----------------------------------------------------

void Drops::serverConnection(){
  char cURL[16];
  url.toCharArray(cURL,16);
  socketIO.on("buttonPressed", std::bind(&Drops::eventWrite, this, std::placeholders::_1, std::placeholders::_2));
  socketIO.on("connect", std::bind(&Drops::connectFunction, this, std::placeholders::_1, std::placeholders::_2));
  socketIO.begin(cURL, 8080);
}

void Drops::loop(){
  socketIO.loop();
}

// ------------------------------------------------------------- Function wifiConnection -----------------------------------------------------

void Drops::wifiConnection(String ssid, String pass){
  char cSSID[32];
  char cPass[20];
  //-------- Conexion con la red de WIFI -----------
   ssid.toCharArray(cSSID,32);
   pass.toCharArray(cPass,20);

   WiFi.begin(cSSID, cPass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

//==================

void Drops::eventWrite(const char * payload, size_t length) {
  deserializeJson(docJson, payload);
    
  String nameButton = docJson["button"];
  bool stateButton = docJson["state"];
  //Aqui activo una funcion del usuario que recibe 
  //stateButton y nameButton
  fp(nameButton,stateButton);
}

void Drops::connectFunction(const char * payload, size_t length) {
  socketIO.emit("ESP32Join", id); 
}
