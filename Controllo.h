#ifndef Controllo_h
#define Controllo_h
#include <Servo.h> 

class Controllo {
  public:
  Servo servo;

  int pin[6] = {
    9, // Servo motore 1
    6, // Servo motore 2
    5, // Servo motore 3
    3, // Servo motore 4
    11, // Servo motore 5
    10 // Servo motore 6
  };

  Controllo();
  void controllaStatus();
  void prendiOggetto();
  void run(int item, int grade);
  void stampaParola(char* ptr);
  void stampaStatus(char* ptr, int item, bool value);
  void svuotaMemoria();
};

#endif