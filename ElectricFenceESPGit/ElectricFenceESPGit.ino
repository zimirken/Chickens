/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";


long FenceDelay = 7;                 //default delay between fence pulses, in 100ms increments
int FenceTime = 5;                   //default time in ms to power the fence charger
int FenceOn = 1;                     //fence defaults to on in case of power outage
unsigned long FencePreviousMillis = 0;
unsigned long FenceInterval = 0;


void setup()
{
  pinMode(3,OUTPUT);           //fence control
  digitalWrite(3, LOW);
  pinMode(1, OUTPUT);          //wifi connected status goes to builtin (active low) LED on ESP-01
  digitalWrite(1,HIGH);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  //turns on built in LED when connected to wifi. You can comment all this out if you don't need it.
  if (WiFi.status() == WL_CONNECTED){
    digitalWrite(1,LOW);
  }
  else {
    digitalWrite(1,HIGH);
  }

  
  Blynk.run();

  //This drives the electric fence circuit
  unsigned long currentMillis = millis();

    FenceInterval = FenceDelay * 100;
  
  if ((currentMillis - FencePreviousMillis >= FenceInterval) && FenceOn)  {
      FencePreviousMillis = currentMillis;
      digitalWrite(3, HIGH);
      delay(FenceTime);                   //its a really short time of a few ms so it's not worth doing anything fancier than a delay.
      digitalWrite(3, LOW);
  }

  if (FenceOn == 0) {
    digitalWrite(3, LOW);
  }

  
}

//these allow you to edit the fence pulse rate and fence charge time in the blynk app if needbe. 
//I've found that the above defaults work best for me.
BLYNK_WRITE(V7)
{
  FenceDelay = param.asLong();
}

BLYNK_WRITE(V8)
{
  FenceTime = param.asInt();
}

BLYNK_WRITE(V9)
{
  FenceOn = param.asInt();
}
