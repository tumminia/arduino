#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include "Controllo.h"
#define OLED_RESET 4
#define MAX 5
#define RUN 4
#include <Servo.h>
#include <string.h> 

Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

Controllo::Controllo(){}

/*
* La funzione controllaStatus è una funzione,
* verifica il corretto funzionamento dei servo motori elettici dal 1 al 5, 
* chiama la funzione stampaStatus, utilizzata per inviare un feedback di esito positivo o negativo.
*/
void Controllo::controllaStatus() {
  Serial.begin(9600);
  char* word = "";
  bool value = false;

  svuotaMemoria();

  int grade = 5;
  for(int i=0;i<MAX;i++) {
    servo.attach(pin[i]);
    servo.write(grade);
    stampaStatus("STATUS", pin[i], servo.attached());
    servo.detach();
    delay(2000);
  }
}

/*
* La funzione StampaStatus è una funzione void,
* stampa a video sul display e sulla console un feedback del funzionamento del servo motore elettrico.
* Quindi se il valore bool value è uguale 1 significa esito positivo,
* se no è uguale a 0 che significa esito negativo.
*/
void Controllo::stampaStatus(char* ptr, int item, bool value) {
  String stringa = String(ptr) + " PIN " + item + ":" + value;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,30);
  display.clearDisplay();
  display.println(stringa);
  display.display();

  Serial.begin(9600);
  Serial.println(stringa);

  delay(3000);
}

/*
* La stampaParola è funzione void,
* stampa a video sul display e sulla console un feedback di inizio e fine di esecuzione del kit Arduino.
*/
void Controllo::stampaParola(char* ptr) {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(30,30);
  display.clearDisplay();
  display.print(ptr);
  display.display();

  Serial.begin(9600);
  Serial.println(ptr);
  delay(3000);
}

/*
* La funzione prendiOggetto è una funzione void,
* ha come obiettivo di prendere un oggetto di piccole dimensioni come una pallina o una gomma,
* chiamando la funzione run.
*/
void Controllo::prendiOggetto() {
  svuotaMemoria();

  /* apre il gancio */
  run(4, 30);

  /* Abbassa il braccio robitco */
  run(1, 60);
  
  /* allunga il braccio robotico */
  run(2, 5);

  /* Chiude il gancio */
  run(4, 90);
  
  /* Sposta all'indietro il braccio robotico */
  run(1, 240);
}

/*
* La funzione run è funzione void,
* che riceve come input il servo motore e l’angolo che deve eseguire la rotazione,
* e chiama anche StampaStatus per inviare un feedback sullo stato;
* int item è il motore che deve ruotare
* int grade è l'angolo di rotazione  
*/
void Controllo::run(int item, int grade) {
  /* Seleziona il motore elettrico */
  servo.attach(pin[item]);
  
  /*
  * controlla la posizione del motore,
  * se è differente ruota il motore
  */
  if(servo.read()!=grade) {
    servo.write(grade);
    stampaStatus("STATUS", pin[item], servo.attached());  
  }
  
  delay(1000);
}

/*
* La funzione svuotaMemoria è funzione void,
* controlla ogni cella di memoria EEPROM se è piena,
* in caso di esito positivo riceve un valore diverso da zero e la sovrascrive impostandolo a 0.
*/
void Controllo::svuotaMemoria() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  for(int i=0;i<EEPROM.length();i++) {
    /*
    * controlla se la cella nella posizione i è piena,
    * se si la svuota impostando il valore a 0
    * se no passa alla cella successiva i+1
    */
    if(EEPROM.read(i)!=0) {
      EEPROM.write(i, 0);
    }
  }
}