#include "heltec.h" 

#define BAND    868E6  // You can set the band here directly, e.g., 868E6, 915E6
String rssi = "RSSI --";
String packSize = "--";
String packet;
unsigned int counter = 0; // Compteur global pour les paquets reçus

// Fonction pour afficher les données sur l'écran Heltec
void LoRaData() {
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Received " + packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0, 15, 128, packet);
  Heltec.display->drawString(0, 40, "Counter: " + String(counter)); // Afficher le compteur
  Heltec.display->display();
}

// Fonction callback pour traiter les paquets reçus
void cbk(int packetSize) {
  packet = "";  // Effacer les données du paquet précédent
  packSize = String(packetSize, DEC);  // Convertir la taille du paquet en chaîne
  
  // Lire les données du paquet
  for (int i = 0; i < packetSize; i++) { 
    packet += (char) LoRa.read(); 
  }

  // Incrémenter le compteur
  counter++;

  // Afficher les données dans le Moniteur Série
  //Serial.println("Message Received: ");
  Serial.println(packet);
 // Serial.println("Counter: " + String(counter)); // Afficher le compteur

  // Mettre à jour l'écran Heltec avec les données reçues
  LoRaData();
}

void setup() { 
  // Initialiser la communication série
  Serial.begin(115200);
  
  // Initialiser Heltec et LoRa
  Heltec.begin(true , true , true , true , BAND );
  
  // Initialiser l'écran Heltec
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  delay(1000);

  if (Heltec.display->init()) {
    Serial.println("OLED initialized successfully");
  } else {
    Serial.println("OLED initialization failed");
  }
  
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->drawString(0, 10, "Wait for incoming data...");
  Heltec.display->display();
  delay(1000);

  // Mettre le module LoRa en mode réception
  LoRa.receive();
}

void loop() {
  // Vérifier si un paquet est reçu
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    cbk(packetSize);  // Traiter le paquet reçu
  }
  delay(10);
}