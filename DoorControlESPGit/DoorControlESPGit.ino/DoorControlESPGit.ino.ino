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

int lastup = 0;
int lastdown = 0;



void setup()
{
  pinMode(1,INPUT);                         //door sensor 1
  pinMode(3,INPUT);                         //door sensor 2

  //motor relay outputs need no programming, as they are driven directly by the blynk app.
  pinMode(2,OUTPUT);                        //motor relay 1
  digitalWrite(2, LOW);
  pinMode(0, OUTPUT);                       //motor relay 2
  digitalWrite(0,LOW);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  
  Blynk.run();

//only writes to blynk when there is a change. reduces blynk writes.
  if (digitalRead(1) != lastup) {
    lastup = digitalRead(1);
    Blynk.virtualWrite(V0, 255-(255*digitalRead(1)));
  }

  if (digitalRead(3) != lastdown) {
    lastdown = digitalRead(3);
    Blynk.virtualWrite(V1, 255-(255*digitalRead(3)));
  }
  
}



