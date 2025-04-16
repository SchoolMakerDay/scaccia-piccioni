/*
Palla di natale

  Esegue canti di natale in modo casuale usando un DFPlayer Mini
  Comando pin 14 logica negativa play brano casuale
  Collegamento con player pin 17 TxD e pin 16 RxD
  Collegamento via bluetooth play brano indicizzato 
*/
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "BluetoothSerial.h"
#define WAKETIME 300000L
DFRobotDFPlayerMini player;
BluetoothSerial SerialBT;
int oldbutton;
int newbutton;
long startwaketime;
int nplay;
void setup() {
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_14, 0);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(14,INPUT_PULLUP);
  oldbutton=digitalRead(14);
  startwaketime=millis();
  Serial.begin(9600);
  delay(2000);
  Serial.println(F("Starting"));
  Serial.println(startwaketime);
  SerialBT.begin("Xmasball"); 
  delay(2000);
  Serial2.begin(9600);
  delay(2000);
  if (!player.begin(Serial2)) {  //Use Serial2 to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));  
  player.volume(30);  //Set volume value. From 0 to 30
  randomSeed(analogRead(0));
}

// the loop function runs over and over again forever
void loop() {
  //check local button
  newbutton=digitalRead(14);
  if((oldbutton!=newbutton)&&(newbutton==LOW)){
    int rnd=random(1,13);
    Serial.println(rnd);
    player.play(rnd);  //Play a random mp3
    startwaketime=millis();
  }
  oldbutton=newbutton;
  //check data from BT
  if (SerialBT.available()) {
    char rxchar=SerialBT.read();
    switch(rxchar){
      case '1':
        player.play(1);
        break;
      case '2':
        player.play(2);
        break;
      case '3':
        player.play(3);
        break;
      case '4':
        player.play(4);
        break;
      case '5':
        player.play(5);
        break;
      case '6':
        player.play(6);
        break;
      case '7':
        player.play(7);
        break;
      case '8':
        player.play(8);
        break;
      case '9':
        player.play(9);
        break;
      case 'A':
        player.play(10);
        break;
      case 'B':
        player.play(11);
        break;
      case 'C':
        player.play(12);
        break;
    }
    startwaketime=millis();
    Serial.println(rxchar);
  } 
  //check sleep mode
  long nowwaketime=millis()-startwaketime;
  //Serial.println(nowwaketime);
  if (nowwaketime > WAKETIME) {
     startwaketime=millis();
     Serial.println("waketime ended");
     Serial.println(nowwaketime);
     Serial.println("Going to sleep now");
     delay(1000);
     esp_deep_sleep_start();
     Serial.println("This will never be printed");
  }
  delay(250);
}
