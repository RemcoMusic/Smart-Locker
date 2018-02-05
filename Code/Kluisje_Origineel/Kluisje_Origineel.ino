#include <Wire.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#define PIRSENSOR_PIN 5


//=======================================================

SoftwareSerial mySerial(2, 3); //2 Green wire is the input from the fingerprint sensor. 3 White wire is the output from the arduino
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//=======================================================
// Variables

bool state_pirsensor = false;    // By default no motion detected by the PIR Sensor
int pirsensorValue = 0;      // Variable to store the sensor status
unsigned long starttime;                // Set the start time of the loop for the enabling of the Fingerprint Sensor
unsigned long endtime;                  // Set the end time of the loop for the enabling of the Fingerprint Sensor

void setup()
{
  pinMode(PIRSENSOR_PIN, INPUT);  //Initialize Pir Sensor as input

  
  Serial.println("Fingerprint Sensor Test");  Serial.begin(9600);

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
  starttime = millis();
  endtime = starttime;
  pirsensorValue = digitalRead(PIRSENSOR_PIN);

    Serial.println("PirValue: " + pirsensorValue);


  
  if(pirsensorValue)             // If there is a motion detected the pin will get a HIGH signal
  {
    while((endtime - starttime) <= 5000) // This loop is now taking 30 seconds (in milliseconds it is 30000)
    {
      endtime = millis();
      int currentFinger = getFingerprintIDez();
      if(currentFinger == 1)
      {
        Serial.println("This is a test");
      } 
    }
    if (!state_pirsensor) 
    {
      Serial.println("Motion detected!"); 
      state_pirsensor = true;       // Update the PIR Sensor variable state to HIGH
    }
  }
  else
  {
    if (state_pirsensor)
    {
        Serial.println("Motion stopped!");
        state_pirsensor = false;               // Update the PIR Sensor variable state to LOW
    }
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
