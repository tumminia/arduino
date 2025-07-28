#include "Controllo.h"

Controllo object;

void setup() {
  object.controllaStatus();
}

void loop() {
  
  object.stampaParola("INIZIO");
  object.svuotaMemoria();
  object.prendiOggetto();
  object.stampaParola("FINE");
  
  exit(0);
}