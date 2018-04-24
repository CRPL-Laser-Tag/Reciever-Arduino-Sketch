#include <IRremote.h>
int RECV_PIN = 9;
int BUZZ_PIN = 8;
int lives = 5;
int delayI = 0;
bool deadF = true;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  digitalWrite(11, HIGH);

}
void loop() {
  if (irrecv.decode(&results) && lives > 0) {
    Serial.println(results.value, HEX);
    digitalWrite(BUZZ_PIN, HIGH);
    delay(100);
    delayI = 2000;
    digitalWrite(BUZZ_PIN, LOW);
    lives--;
      if (lives == 0) {
        //digitalWrite(BUZZ_PIN, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        if (deadF == true) {
          digitalWrite(BUZZ_PIN, HIGH);
          delay(2000);
          digitalWrite(BUZZ_PIN, LOW);
          deadF = false;
        }
      }
      if (lives == 3) {
        digitalWrite(10, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        if (deadF == false) {
          deadF = true;
        }
      }
      delay(delayI);
      if (delayI > 0) {
        irrecv.resume(); // Receive the next value
        delayI = 0;
      }
    }
  }



