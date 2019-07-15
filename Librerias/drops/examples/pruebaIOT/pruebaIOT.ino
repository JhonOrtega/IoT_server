#include <drops.h>
#define LED_BUILTIN 2

#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

Drops drop("209.182.218.174","5d235dfaa0a6af389c9de946","5d2c9fb9c1da9b8ab6197e88");
int vectorI[5];

int tiempo;
long t_antes;

void myFuncion(String nameButton,bool stateButton){
  Serial.println(nameButton);
  Serial.println(stateButton); 
  digitalWrite(LED_BUILTIN,stateButton); 
}
// ---------------------------------------------- SETUP --------------------------
void setup() {
  Serial.begin(115200);
  
  drop.wifiConnection("RED-UDENAR","123456789");
  drop.serverConnection();
  
  t_antes = millis();
  pinMode(LED_BUILTIN,OUTPUT);
   
  drop.sendData("boton",false);
  drop.fp = myFuncion;
}
// ----------------------------------------------- LOOP --------------------------
void loop() {
  drop.loop();

  tiempo = 1000;
    
  if(millis()-t_antes>tiempo){
      vectorI[0]= random(0,100);
      vectorI[1]= random(0,100);
      vectorI[2]= random(0,100);
      vectorI[3]= random(0,100);
      vectorI[4]= random(0,100);
      drop.sendData("voltage",vectorI,ARRAY_SIZE(vectorI));
      t_antes = millis();
  }
}
