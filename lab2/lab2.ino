#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//create every varible to connect to wifi
char auth[] = "b1VFIjb9nj3neVO2BATKybUdb6-5O3eU";
char ssid[32] = "utguest";
char pass[32] = "";

#define LED 2 //define the led

//ROM varibles
const int freq = 5000;
const int ledChannel = 0;  
const int resolution = 10;

//RAM varibles for timer
int timecount = 0;
String w = ""; 

BlynkTimer timer;//creates the timer

//send info to both the terminal and the dispaly
void myTimerEvent()
{
    if (timecount == 100)
    {
      Blynk.virtualWrite(V2, millis() / 1000); // Write the arduino uptime every second
      timecount = 0;
    }

    else 
    {
      char character;
      while (Serial.available ())
      {
        character = Serial.read ();
        w.concat (character);
      }
      if (w != "")
      {
        Blynk.virtualWrite (V3, w);
        w = "";
      }
    }
    timecount += 1;
}

// Note the different pin setup function!
void setup() {
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
    timer.setInterval(10L, myTimerEvent);//calls timer every second
  
    // configure LED PWM functionality
    ledcSetup (ledChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin (LED, ledChannel);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}

BLYNK_WRITE (V0)
{
  int pinValue = param.asInt();

  if (pinValue == 1)
    ledcWrite(ledChannel, 0);//set LED low
    
  else
    ledcWrite(ledChannel, 1023);//set LED high
}

// If virtual pin 2 controls fade value, 0 to 1023.
BLYNK_WRITE(1)
{
    // param is a member variable of the Blynk ADT. It is exposed so you can read it.
    int val = param.asInt(); // assigning incoming value from pin V1 to a variable
    ledcWrite(ledChannel, val); // Note that this takes ledChannel as an argument, NOT the pin! Set duty = val.
}
