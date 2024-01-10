/********************************
*   NutzloseBox für Bernhard    *
*            AI-Team
********************************/

// Includes
#include <Servo.h>

// Setup
Servo myservo_deckel; // Servo für Deckel initialisieren
Servo myservo_finger; // Servo für Finger initialisieren

const int Pin_deckel = 6; // Eingang am Arduino für Servo Deckel
const int Pin_finger = 9; // Eingang am Arduino für Servo Finger
const int Pin_WS = 2;     // Eingang am Arduino für Wippschalter

int n = 0; // default action index


// Anfangspositionen definieren (müssen evtl. angepasst werden)
const int DeckelBeginPos = 90; // '100°' Deckel geschlossen
const int FingerBeginPos = 2;  //Grad müssen evtl. angepasst werden
// Endpositionen definieren
const int DeckelEndPos = 10; // '0°' --> Deckel voll geöffnet
const int FingerEndPos = 2;  //Grad müssen evtl. angepasst werden


//int pos = 0;
//int action = 0;


// Initialisierung einiger Funktionen
void setup() {
  // put your setup code here, to run once:

  pinMode(Pin_WS, INPUT_PULLUP);

  myservo_deckel.attach(Pin_deckel); //myservo_deckel für die Klappe
  myservo_finger.attach(Pin_finger); //myservo_finger für den Finger

  // Zur Ersteinrichtung
  //myservo_deckel.write(0); einkommentieren und Heleb einstellen

  // Servos in Ausgangsstellung fahren
  myservo_deckel.write(DeckelBeginPos);
  myservo_finger.write(FingerBeginPos);

}


// MAIN
void loop() {
  // put your main code here, to run repeatedly:

  // Wenn Wippschalter betätigt wurde...
  if(digitalRead(Pin_WS) == LOW) {
    // zufällige Aktion durchführen
    action();
  }
  delay(1000);
}


// Actions
void action() {
  n = random(2);  // random n: n entspricht Anzahl der vordefinierten cases + 1!
  //n = 1; // zum debuggen case vorgeben (muss später auskommentiert werden!)
  delay(500);
  switch(n) {
    case 0:
      openDeckel();
      delay(500);
      closeDeckel();
      break;
    case 1:
      openDeckelSlow();
      delay(500);
      closeDeckelSlow();
      break;
    case 2:
      break;
    default:
      break;
  }
}


/***************
*  Funktionen  *
***************/

void openDeckel() {
  myservo_deckel.attach(Pin_deckel);
  myservo_deckel.write(DeckelEndPos);
  delay(1000);
}

void openDeckelSlow() {
  myservo_deckel.attach(Pin_deckel);
  for(int i = DeckelBeginPos; i >= DeckelEndPos; i--) {
    myservo_deckel.write(i);
    delay(50);
  }
}

void closeDeckel() {
  myservo_deckel.write(DeckelBeginPos);
  delay(1000);
  myservo_deckel.detach();
}

void closeDeckelSlow() {
  for(int i = DeckelEndPos; i <= DeckelBeginPos; i++) {
    myservo_deckel.write(i);
    delay(50);
  }
  myservo_deckel.detach();
}

