/*
 SENSOR_LIGHTS: Potentiometer >> LED (Single Channel Script)
 
 This example dims light levels using an LED on pin 11
 and a potentiometer on A0. 
 
 Created by Ryan Achten | SOMA | somavisions.com
 
 This example code is in the public domain.
 */




int potentLevel;
int ledLevel;

//*************************CHECK*****************************

int led = 11;           // the pin that the LED is attached to
int inputPin = A0;      // the pin that the potentiometer is attached to

//*************************CALIBRATE*************************

const int numReadings = 1;  //change this to alter the number of values to be averaged
int potentMin = 0; 
int potentMax = 700;        //maximum output from potentiometer
int loopDelay = 100;       //delay time between loops. Too low may cause overclocking  
//                            while too high may cause delayed sensor response

//***********************************************************

int potentAve = 0;
int readings[numReadings];
int index = 0;
int total = 0;





// the setup routine runs once when you press reset:
void setup()  { 

  //*************************POTENT >> LED SETUP CODE*************************

  Serial.begin(38400);

  pinMode(led, OUTPUT);


  //***************************SMOOTH SETUP CODE*****************************
  // initialise all the readings to 0: 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;  

} 


//****************************SMOOTH LOOP CODE****************************

void loop()  { 

  total= total - readings[index];         
  readings[index] = analogRead(inputPin); 
  total= total + readings[index];       
  index = index + 1;  

  if (index >= numReadings)              
    index = 0;                           

  potentAve = total / numReadings;         
  Serial.print("Average Potentiometer Readings: ");
  Serial.println(potentAve);   



  //*************************POTENT >> LED LOOP CODE*************************

  ledLevel = map(potentAve, potentMin, potentMax, 0, 255);
  Serial.print("LED Level: ");
  Serial.println(ledLevel, DEC);
  analogWrite(led, ledLevel);

  Serial.println();
  delay(loopDelay);


}











