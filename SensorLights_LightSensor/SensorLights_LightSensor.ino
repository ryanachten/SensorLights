/*
 SENSOR_LIGHTS: Light sensor module >> LED (Single Channel Script)
 
 This example steps through brightness levels using an LED on pin 11
 and a light sensor module on A0. 
 
 Created by Ryan Achten | SOMA | somavisions.com
 
 This example code is in the public domain.
 */

//NOTE:
//if oscillation in the sensor reading occurs during breadboard phase
//it will probably be an issue with the wiring of the sensor


int lightLevel; //sensor readings
int ledLevel; //led strip brightness output 0 -> 255

//*************************CHECK*****************************

int led = 11; //the pin the LED is attached to
int inputPin; //the pin the input component is attached to


//*************************CALIBRATE*************************

const int numReadings = 5;  //change this to alter the number of values to be averaged
//                          the higher the number the smoother (and less accurate) the results
int delayTime = 100;       //delaytime between loops. 50 -> 100 operational
//                         100 -> 200 for testing/calibration
//                         Too low may cause overclocking 
int lightMin = 0;          //minimum light level. 
//                         Typically set at 0 unless offset is desired.
int lightMax = 800;        //light level will map wrong if this is set wrong - 
//                         find highest reading and replace to match environment
int dayLight = 50;         //find 'daytime level' / average resting value and 
//                         replace the value with this. If light is above the LED is off

//***********************************************************

int lightAve = 0;
int readings[numReadings];
int index = 0;
int total = 0;

//*******************LIGHT >> LED SETUP CODE*****************


void setup(){
  Serial.begin(38400);
  pinMode(led, OUTPUT);

  //***************************SMOOTH SETUP CODE***************************** 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;  

}

//*************************LIGHT >> LED LOOP CODE*************************

void loop(){
  lightLevel = analogRead(inputPin);
  Serial.print("Light Level: ");
  Serial.println(lightLevel, DEC);

  if (lightLevel < dayLight){
    ledLevel = map(lightAve, lightMin, lightMax, 255, 0);
    Serial.print("LED Level: ");
    Serial.println(ledLevel, DEC);
  }
  else {
    ledLevel = 0;
    Serial.print("!DAYTIME! LED level = 0");
  }
  analogWrite(led, ledLevel);
  Serial.println();
  delay(delayTime);
}





