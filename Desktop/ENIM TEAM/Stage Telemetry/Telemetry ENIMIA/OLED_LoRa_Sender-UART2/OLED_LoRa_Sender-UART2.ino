#include "heltec.h"

#define BAND    868E6  // you can set band here directly, e.g., 868E6, 915E6
#define RX 23
#define TX 17

unsigned int counter = 0;

void setup()
{ 
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX, TX);
  Heltec.begin(true /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1000);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  delay(1000);
}

void loop()
{
  // Read data from Serial2
  if (Serial2.available()) {
    //String receivedData = Serial2.readString() + "                                     " + String(counter);
    String receivedData = Serial2.readString();

    // Print to Serial Monitor
    Serial.println("Message Received: ");
    Serial.println(receivedData);

    // Display on Heltec screen
    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT); 
    Heltec.display->drawString(0, 0, "Sending packet: ");
    Heltec.display->drawString(0, 10, String(counter)); // ?
    Heltec.display->drawString(0, 20, receivedData);
    Heltec.display->display();

    // Send packet via LoRa
    LoRa.beginPacket();
    LoRa.print(receivedData);
    LoRa.endPacket();
    counter++;
  }
  /*else {
    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10); // Ligne 17
    Heltec.display->drawString(0, 0, "error ");
    Heltec.display->display();
    Serial.println("No message ");
    delay(700);
  }*/
}