/*******************************************************************
    Plays the Zelda Chest Jingle on startup using
    a passive speaker. Runs on an attiny85

    Originally written by ianklatzco:
    https://gist.github.com/ianklatzco/9127560
                                                                 
    Modified by Brian Lough
    https://www.youtube.com/channel/UCezJOfu7OtqGzd5xrP3q6WA

    Modified by Alexis Reyes
    This versión will have a system into a chest, the desing provide LDR sensor taht it'll be activated when the chest open.Added also a led with PWM. 
 *******************************************************************/


const int led = 6;
const int LDR_sensor = A5;
const int speakerPin = 9;
int light_treshold = 100;
int i;

char notes[] = "gabygabyxzCDxzCDabywabywzCDEzCDEbywFCDEqywFGDEqi        azbC"; // a space represents a rest
int length = sizeof(notes); // the number of notes
int beats[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 3, 16,};
int tempo = 150;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'x', 'a', 'z', 'b', 'C', 'y', 'D', 'w', 'E', 'F', 'q', 'G', 'i' };
  // c=C4, C = C5. These values have been tuned.
  int tones[] = { 1898, 1690, 1500, 1420, 1265, 1194, 1126, 1063, 1001, 947, 893, 843, 795, 749, 710, 668, 630, 594 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}


void playMelody() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
    
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  //playMelody();
  Serial.begin(9600);
  Serial.println("--- Lecturas entrada LDR ---");
}


void loop() {
  delay(4000);
  int value = analogRead(LDR_sensor);
  delay(1000);
  Serial.println(value);
  if (value > light_treshold) {
     
     for(i=0; i<256; i++){ 
        analogWrite(led,i);
        delay(10);
     }
     playMelody();
     digitalWrite(led,LOW);
     digitalWrite(speakerPin, LOW);
     }
}