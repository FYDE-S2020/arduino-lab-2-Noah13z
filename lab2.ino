#include <Blynk.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "b1VFIjb9nj3neVO2BATKybUdb6-5O3eU";
char ssid[32] = "utguest";
char pass[32] = "";

#define LED 2
/*A global for LED state
A global for current duty cycle
A global Blynk Timer object
A global time counter variable
A global String object for holding messages
A timer event function
two BLYNK_WRITE functions- one for slider, one for button*/

const int freq = 5000;
const int ledChannel = 0;  
const int resolution = 10;

BlynkTimer timer;

/*void setup() {
  Serial.begin(115200);
  pinMode (LED_PIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}

BLYNK_WRITE (V0)
{
  int pinValue = param.asInt();

  if (pinValue == 1)
    digitalWrite (LED_PIN, LOW);
  else
    digitalWrite (LED_PIN, HIGH);
}

BLYNK_READ (V2)
{
  Blynk.virtualWrite (2, millis()/1000);
}*/

// Note the different pin setup function!
void setup() {
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
  
    // configure LED PWM functionality
    ledcSetup (ledChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin (LED, ledChannel);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}

BLYNK_WRITE (V0)
{
  int pinValue = param.asInt();

  if (pinValue == 1)
    ledcWrite(ledChannel, 0);
  else
    ledcWrite(ledChannel, 1023);
}

// If virtual pin 2 controls fade value, 0 to 1023.
BLYNK_WRITE(1)
{
    // param is a member variable of the Blynk ADT. It is exposed so you can read it.
    int val = param.asInt(); // assigning incoming value from pin V1 to a variable
    ledcWrite(ledChannel, val); // Note that this takes ledChannel as an argument, NOT the pin! Set duty = val.
}
