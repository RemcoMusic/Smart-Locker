#include <Wire.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define SLOT1_PIN 8
#define SLOT2_PIN 9
#define SLOT3_PIN 10
#define SLOT4_PIN 11

//=======================================================

SoftwareSerial mySerial(2, 3); //2 Green wire is the input from the fingerprint sensor. 3 White wire is the output from the arduino
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//=======================================================
// Variables

long kans1;
long kans2;
long kans3;
long kans4;

void setup()
{ 
  Serial.begin(9600);
  Serial.println("Fingerprint Sensor Test");  

  pinMode(SLOT1_PIN, OUTPUT);
  pinMode(SLOT2_PIN, OUTPUT);
  pinMode(SLOT3_PIN, OUTPUT);
  pinMode(SLOT4_PIN, OUTPUT);
  
  finger.begin(57600); // Set the data rate for the Fingerprint Sensor serial port

  if (finger.verifyPassword()) 
  {
    Serial.println("Found fingerprint sensor!");
  }
  else 
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
}

void loop()
{
   kans1 = random(5);
   kans2 = random(20);
   kans3 = random(50);
   kans4 = random(100);
   
   int currentFinger = getFingerprintIDez();
   if(currentFinger == -2)
   {
    if(kans1 == 1)
    {
      Serial.println("Kluisje 1");
      digitalWrite(SLOT1_PIN, HIGH);
      delay(5000);
      digitalWrite(SLOT1_PIN, LOW);
    }
    if(kans2 == 1)
    {
      Serial.println("Kluisje 2");
      digitalWrite(SLOT2_PIN, HIGH);
      delay(5000);
      digitalWrite(SLOT2_PIN, LOW);
    }
    if(kans3 == 1)
    {
      Serial.println("Kluisje 3");
      digitalWrite(SLOT3_PIN, HIGH);
      delay(5000);
      digitalWrite(SLOT3_PIN, LOW);
    }
    if(kans4 == 1)
    {
      Serial.println("Kluisje 4");
      digitalWrite(SLOT4_PIN, HIGH);
      delay(5000);
      digitalWrite(SLOT4_PIN, LOW);
    }
   }
   if(currentFinger == 1)
   {
    digitalWrite(SLOT1_PIN, HIGH);
    digitalWrite(SLOT2_PIN, HIGH);
    digitalWrite(SLOT3_PIN, HIGH);
    digitalWrite(SLOT4_PIN, HIGH);
    delay(5000);
    digitalWrite(SLOT1_PIN, LOW);
    digitalWrite(SLOT2_PIN, LOW);
    digitalWrite(SLOT3_PIN, LOW);
    digitalWrite(SLOT4_PIN, LOW);
   }
}


int getFingerprintIDez() // This method returns -1 if the fingerprint scan failed, otherwise it will returns it stored ID #
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1; 

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -2;

  Serial.print("This following ID is scanned: ");
  Serial.println(finger.fingerID);
  return finger.fingerID;
}
