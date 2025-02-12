#include "heltec.h"

#define BAND    868E6  //you can set band here directly,e.g. 868E6,915E6

#define RX 23
#define TX 17

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;


void setup()
{ 
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RX, TX);
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, false /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop()
{
  Serial.println("Message Received: ");
  Serial.println(Serial2.readString());

  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Sending packet: ");
  Heltec.display->drawString(0,10, String(counter));
  Heltec.display->drawString(0,20, String(Serial2.readString()));
  Heltec.display->display();

  // send packet
  LoRa.beginPacket();
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print(Serial2.readString());
  LoRa.endPacket();

  counter++;
              
}
