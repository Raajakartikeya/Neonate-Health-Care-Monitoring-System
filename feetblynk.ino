#define BLYNK_TEMPLATE_ID "TMPLWvXvPmdD"
#define BLYNK_DEVICE_NAME "Sample"
#define BLYNK_AUTH_TOKEN "reemUhv-KVvTWwWz2oyh9svlOdWCiXCk"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Raaja";  
char pass[] = "raaja12345"; 


#define REPORTING_PERIOD_MS     1000

float BPM, SpO2;

/*Put your SSID & Password*/

BlynkTimer timer;

PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(16, OUTPUT);
  delay(100);

  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
    
  }
}
void loop() {
  Blynk.run();
  timer.run();
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {

    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();

    Serial.print("BPM: ");
    Serial.println(BPM);

    Serial.print("SpO2: ");
    Serial.print(SpO2);
    Serial.println("%");

    Serial.println("*********************************");
    Serial.println();
    tsLastReport = millis();
  }
  Blynk.virtualWrite(V2,BPM);
  Blynk.virtualWrite(V4,SpO2);
}
