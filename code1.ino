#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>



#include <AX12A.h>



#define DirectionPin  (10u)

#define BaudRate      (1000000ul)

#define ID            (1u)



char auth[] = "Blynk Auth Token";

char ssid[] = "Your SSID";

char pass[] = "Wifi password";



int speed = 100;



void setup()

{

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

 

  delay(1000); // Give time for Dynamixel to start on power-up 

  ax12a.begin(BaudRate, DirectionPin, &Serial);

  

 }





void loop()

{

 

  Blynk.run();

 

}





BLYNK_WRITE(V1)

{

  int x = param[0].asInt();

  int y = param[1].asInt();



  if( (x > 0) && (x <500) ){ // turn left

      

      ax12a.setEndless(ID, ON);

      ax12a.turn(ID, LEFT, speed);

     

  }else if( (x> 512) && ( x < 1023) ){ // turn right

      

      ax12a.setEndless(ID, ON);

      ax12a.turn(ID, RIGHT, speed);

      

  }else{

      ax12a.turn(ID,RIGHT,0);

  }

  

}

BLYNK_WRITE(V2)

{

  if( param.asInt() == 1 ){

     ax12a.setEndless(ID, OFF);

     ax12a.moveSpeed(ID,0,speed);

  }

}

BLYNK_WRITE(V3)

{

  if( param.asInt() == 1 ){

   ax12a.setEndless(ID, OFF); 

   ax12a.moveSpeed(ID,180,speed);

  }

}



BLYNK_WRITE(V4)

{

   speed = param.asInt();

}
