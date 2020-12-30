#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>

const char *devAddr = "26011460";
const char *nwkSKey = "6A9A748C8D3FD8FABF0676303586CF2F";
const char *appSKey = "6C543B9F868CD324503F11C92267081B";

SoftwareSerial loraSerial(10, 11);
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868


TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(9600);
  debugSerial.begin(9600);

  pinMode(9,OUTPUT);
  pinMode(A0,INPUT);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey);

  debugSerial.println("-- STATUS");
  ttn.showStatus();
}

void loop()
{
  debugSerial.println("-- LOOP");

  // Prepare payload of 1 byte to indicate LED status
  //byte payload[1];
  //payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;

  digitalWrite(9,HIGH);
  delay(200);
  
  uint32_t tension = analogRead(A0);
  
  digitalWrite(9,LOW);
  delay(200);

  debugSerial.println("Mesure: " + String(tension));
  
  byte payload[2];
  payload[0]=highByte(tension);
  payload[1]=lowByte(tension);
  
  ttn.wake();
  ttn.sendBytes(payload, sizeof(payload));
  ttn.sleep(1000);

  delay(1000);
}
