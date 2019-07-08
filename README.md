# UDENAR_IoT_ServerLibrary
This is a library of UDENAR server for ESP32S and Particle Photon devices.

## Supported ESP32S and Particle Photon devices

## Usage

Set up the hardware:
- A MPU9250 device with I2C Protocol

Flash the [mpu9250 example](examples/readsensors/readsensors.ino).

Adapt it to your needs while keeping this general structure:

```cpp
MPU9250 margSensor();
int16_t dataSensor[10];

void setup() {
  margSensor.begin();
}
void loop() {
  margSensor.Read9Axis(dataSensor);
  // The sensor values is stored in dataSensor[x] as follows:
  // dataSensor[0] ~ dataSensor[2] (Acceleration X Axis - Acceleration Y Axis - Acceleration Z Axis)
  // dataSensor[3] (Temperature)
  // dataSensor[4] ~ dataSensor[6] (AngularRate X Axis - AngularRate Y Axis - AngularRate Z Axis)
  // dataSensor[7] ~ dataSensor[9] ( MagneticComponent X Axis - MagneticComponent Y Axis - MagneticComponent Z Axis)
}
```

## Documentation

### Server connection

``Drops drop("209.182.218.174","idUser","idProject");
idUser: 
idProject: ``

Sets up the connection with the server.

### WiFi connection

``drop.wifiConnection("ssid","password");``

This function allows the microcontroller to connect to WiFi.

### Send Data to the server

```
drop.sendData("name",data/state/"text");
```
This function allows us to send data to the srever
The first argument is the name of the field or variable to be used; the second argument is the data to be sent:
```
drop.sendData("name",132.127); // send numbers: int, float or double
drop.sendData("name",true); // send state: bool
drop.sendData("name","text"); // send text: String
```
If you want to send an Array, use:
```
drop.sendData("name",myArray,size);
```
The first argument is the name of the field or variable to be used, the second argument is the array with data to be sent and the third one is the size of the array (ARRAY_SIZE()):
```
drop.sendData("name",myArray,ARRAY_SIZE(myArray)); // send array: int, float or double
```

### Calculate ARRAY_SIZE
```
#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif
```
Declare this function before the setup loop.



## Nuances

## References

- MPU-9250 Product Specification Revision 1.1(http://www.invensense.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf) (Invensense)
- MPU-9250 Register Map and Descriptions Revision 1.6(https://www.invensense.com/wp-content/uploads/2015/02/RM-MPU-9250A-00-v1.6.pdf) (Invensense)
- AK8963 Datasheet(https://www.akm.com/akm/en/file/datasheet/AK8963C.pdf) (Asahi Kasei)

## License
Copyright 2018-2022 JDVR, Juan David Velasquez Rosero

Released under the LGPL license
