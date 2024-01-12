/***************************************************
/* Magnetkartenlesegerät - Escape-Room-Edition              */
/* Wolfgang Winkelsträter - bit-saar.de           */
/* program status: 2023/03                        */
/* Version 1                                      */
/* Modul: Nano V3 (oldBootloader)                 */
/*                                                */
/***************************************************/
  
#include <PS2Keyboard.h>

const int signalpin = 9;
const int DataPin = 8;
const int IRQpin =  2; // 

char* code = "49735?";

int currentPosition = 0;
int correctChar = 0;

PS2Keyboard keyboard;


void setup() {

  pinMode(signalpin, OUTPUT);
  digitalWrite(signalpin, HIGH);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Magnetkartenlesegerät - Escape-Room-Edition");
  Serial.println("Version 1 - 2023/03");
  Serial.println("(C) Wolfgang Winkelsträter - bit-saar.de");
  Serial.println("Modul: Nano V3 (oldBootloader)");
  Serial.println("PIN: D8 - Data"); 
  Serial.println("D2 - IRQ");
  Serial.println("D9 - Signalpin");
}

void loop() {
  if (keyboard.available()) {
      
    // read the next key
    char card = keyboard.read();
    
    Serial.println(card);
    
    if (card == code[currentPosition]){
      ++currentPosition;
      ++correctChar;
    }

    else{
      currentPosition = 0;
      correctChar = 0;
    }

    if(currentPosition == 6 && correctChar == 6){
     Serial.println("Card accepted!");
      digitalWrite(signalpin, LOW);
      Serial.println("pinhigh!");
      delay(10000);
      digitalWrite(signalpin, HIGH);
      Serial.println("pinlow!");
    }
    
  }
}
