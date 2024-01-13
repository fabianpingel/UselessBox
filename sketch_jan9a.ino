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
const int FingerBeginPos = 55;  // Grad müssen evtl. angepasst werden, max 60!!!
// Endpositionen definieren
const int DeckelEndPos = 10; // '0°' --> Deckel voll geöffnet
const int FingerEndPos = 5;  //Grad müssen evtl. angepasst werden


//int pos = 0;
//int action = 0;



// Initialisierung einiger Funktionen
void setup() {
  // put your setup code here, to run once:

  pinMode(Pin_WS, INPUT_PULLUP);

  myservo_deckel.attach(Pin_deckel); //myservo_deckel für die Klappe
  myservo_finger.attach(Pin_finger); //myservo_finger für den Finger

  // Zur Ersteinrichtung
  //myservo_deckel.write(0); //einkommentieren und Hebel einstellen --> Position, wenn Deckel voll geöffnet
  //myservo_finger.write(0); //einkommentieren und Finger einstellen --> Position, wenn Schalter betätigt + X° Reserve
  // Einstellen der Anfangsposition
  // myservo_finger.write(FingerBeginPos); // Einstellen der Anfangsposition
  // myservo_deckel.write(DeckelBeginPos); // Einstellen der Anfangsposition

  // Einstellen der Endposition  
  //myservo_finger.write(FingerEndPos); // Einstellen der Endposition
 //myservo_deckel.write(DeckelEndPos); // Einstellen der Endposition

  // Servos in Ausgangsstellung fahren
  myservo_deckel.write(DeckelBeginPos);
  myservo_finger.write(FingerBeginPos);
  delay(2000);
  myservo_deckel.detach();
  myservo_finger.detach(); 
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
  n = random(4);  // random n: n entspricht Anzahl der vordefinierten cases + 1!
  //n = 1; // zum debuggen case vorgeben (muss später auskommentiert werden!)
  delay(2000);
  switch(n) {
    case 0: // case 0 nur zum debuggen
      openDeckel();
      delay(500);
      openFinger();
      closeFinger();
      delay(200);
      closeDeckel();
      delay(200);
      break;
    case 1:
      openDeckelSlow();
      delay(1000);
      openFinger();
      delay(20);
      closeFinger();
      delay(500);
      closeDeckelSlow();
      delay(500);
      break;
    case 2:
      fakeDeckel();
      break;
    case 3:
      openDeckel();
      delay(500);
      openFinger();
      closeFinger();
      delay(200);
      closeDeckel();
      delay(200);
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
  delay(500);
}

void openFinger() {
  myservo_finger.attach(Pin_finger);
  myservo_finger.write(FingerEndPos);
  delay(500);
}

void openDeckelSlow() {
  myservo_deckel.attach(Pin_deckel);
  for(int i = DeckelBeginPos; i >= DeckelEndPos; i--) {
    myservo_deckel.write(i);
    delay(50);
  }
  delay(500);
}

void fakeDeckel() {
  for(int i = 0; i < 3; i++) {
    myservo_deckel.attach(Pin_deckel);
    myservo_deckel.write((DeckelBeginPos+DeckelEndPos)/2);
    delay(1000);
    closeDeckel();
  }
}

void closeDeckel() {
  myservo_deckel.write(DeckelBeginPos);
  delay(1000);
  myservo_deckel.detach();
}

void closeFinger() {
  myservo_finger.write(FingerBeginPos);
  delay(1000);
  myservo_finger.detach();
}

void closeDeckelSlow() {
  for(int i = DeckelEndPos; i <= DeckelBeginPos; i++) {
    myservo_deckel.write(i);
    delay(50);
  }
  myservo_deckel.detach();
}

