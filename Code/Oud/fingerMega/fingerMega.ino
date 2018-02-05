#include <Wire.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

int inputPin = 10;               // pr sensor
int val = 0;                    // HIGH or LOW
bool pr = false;
long prev;
int randomNumber;


int getFingerprintIDez();

// pin #11 is IN from sensor (GREEN wire)
// pin #12 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(11, 12); //11 green 12 white



Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  pinMode(2, OUTPUT); //raber bruin
  pinMode(3, OUTPUT); //bradley grijs
  pinMode(4, OUTPUT); //kaan zwart
  pinMode(5, OUTPUT); //remco blauw
  //pinMode(6, OUTPUT); //5v voor pr

  pinMode(inputPin, INPUT);     // declare sensor as input


  Serial.begin(9600);
  Serial.println("fingertest");

  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  }
  else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

}

void loop()                     // run over and over again
{
 // digitalWrite(6, HIGH);
  pr = false;
  val = digitalRead(inputPin);
  Serial.println(val);

  if (val == HIGH) {
    Serial.println("Motion detected!");
    pr = true;
  }


  if (pr == true) {
    prev = millis();

    while (true) {
      if ( millis() - prev >= 10000) {
        break;
      }
      else {
        int vinger = getFingerprintIDez();
        if (vinger == -2) {
          delay(2000);
          break;
         
         
          
        }
        
        if (vinger == 1 || vinger == 2 || vinger == 3 || vinger == 4 || vinger == 5 ) {
           digitalWrite(5, HIGH);
          delay(3000);
          digitalWrite(5, LOW);
          break;
        }

        if (vinger == 8 || vinger == 9 || vinger == 10 || vinger == 11 ) {
          digitalWrite(3, HIGH);
          delay(5000);
          digitalWrite(3, LOW);
          break;
        }

        if (vinger == 14 || vinger == 15 || vinger == 16 || vinger == 17 ) {
         // digitalWrite(6, LOW);
         // delay(500);
          digitalWrite(4, HIGH);
          delay(5000);
          digitalWrite(4, LOW);
          break;
        }

        if (vinger == 228 || vinger == 21 || vinger == 22 || vinger == 23 ) {
          digitalWrite(5, HIGH);
          delay(5000);
          digitalWrite(5, LOW);
          break;
        }
        if (vinger == 6 || vinger == 12 || vinger == 18 || vinger == 24 ) {
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          delay(5000);
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;
        }
        
      }
    }
  }
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {


  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;

  Serial.println(finger.fingerID);
  return finger.fingerID;

}
