# UDENAR IoT Server Library
This is a library to use ESP32 and Particle Photon devices connected with IoT to Udenar's server.

## Particle Photon

### Configure Particle Photon

Use this lines at the beginning of the script.
```
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>
```
Use this line to connect the device to the server and the project that you are going to use:
- idUser: 
- idCloud:
- idDevice:
- Personal access token: 
```
Drops drop("idUser","idCloud","idDevice","access token");
```
### void setup:
If you want to subscribe to the event of a button widget on the web page use:
```
Particle.function("buttonPressed",myFunction);
```
### void loop:
Upload data to the server
```
data = drop.sendData("name",data/state/"text");
if(Particle.connected())Particle.publish("sendData", data,PRIVATE,WITH_ACK);
```
The first argument is the name of the field or variable to be used; the second argument is the data to be uploaded; PRIVATE and WITH_ACK are needed.

### Function event of a button widget
Once subscribed to an event of a button widget as mentioned before, declare a function to have the name of the button pressed and its boolean state:
```
int myFunction(String payload) {
  String nameButton;
  bool stateButton[1];
  nameButton = drop.deserializePayload(payload, stateButton);
  Serial.println(nameButton); //Print on serial the name of the button pressed
  Serial.println(stateButton[0]); // Print on serial the state of the button pressed
  return 0; 
}
```


## ESP32

### Configure ESP32

Use this line to set up the connection of the device with the server and the project that you are going to use:
- idUser: 
. idProject: 
```
Drops drop("209.182.218.174","idUser","idProject");
```
### void setup
##### WiFi connection
This function allows the microcontroller to connect to WiFi.
```
drop.wifiConnection("ssid","password");
```
##### Server connection
Connect the device to the server
```
drop.serverConnection();
```
### void loop
Upload data to the server
```
drop.sendData("name",data/state/"text");
```
The first argument is the name of the field or variable to be used; the second argument is the data to be uploaded.

### Function event of a button widget
Declare a function to have the name of the button pressed and its boolean state:
```
void myFunction(String nameButton,bool stateButton){
  Serial.println(nameButton); //Print on serial the name of the button pressed
  Serial.println(stateButton); //Print on serial the state of the button pressed
}
```
Declare this line on void setup:
```
drop.fp = myFuncion;
```

## Data to be uploaded to the server
In the function
```
drop.sendData("name",data/state/"text");
```
the first argument is the name of the field or variable to be used; the second argument is the data to be sent:
```
drop.sendData("name",123.456); // send numbers: int, float or double
drop.sendData("name",true); // send state: bool
drop.sendData("name","text"); // send text: String
```
If you want to upload an Array, use:
```
drop.sendData("name",myArray,size);
```
The first argument is the name of the field or variable to be used, the second argument is the array with data to be uploaded and the third one is the size of the array.
```
drop.sendData("name",myArray,ARRAY_SIZE(myArray)); // send array: int, float or double
```
#### Calculate ARRAY_SIZE
Declare this function before the setup loop.
```
#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif
```

## References

- MPU-9250 Product Specification Revision 1.1(http://www.invensense.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf) (Invensense)
- MPU-9250 Register Map and Descriptions Revision 1.6(https://www.invensense.com/wp-content/uploads/2015/02/RM-MPU-9250A-00-v1.6.pdf) (Invensense)
- AK8963 Datasheet(https://www.akm.com/akm/en/file/datasheet/AK8963C.pdf) (Asahi Kasei)

## License
Copyright 2018-2022 JDVR, Juan David Velasquez Rosero

Released under the LGPL license
