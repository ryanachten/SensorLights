/*
 SENSOR_LIGHTS: Knock Sensor Module >> LED (Single Channel Script)
 
 This example steps through brightness levels using an LED on pin 11
 and a knock sensor module on A0. 
 
 Created by Ryan Achten | SOMA | somavisions.com
 
 This example code is in the public domain.
 */



int knockLevel;
int ledLevel;

//*************************CHECK*****************************

int led = 11;           // the pin number that the LED strip is attached to
int inputPin = A0;      // the pin that the sensor is attached to

//*************************CALIBRATE*************************

const int numReadings = 1;   //number of samples to averaged before reading
int knockMin = 0;            //lowest recorded sensor value (will typically be 0 unless an offset is required)
int knockMax = 100;          //highest recorded sensor value (dependent on use-case)
int loopDelay = 100;       //delay time between loops. Too low may cause overclocking  
                             //while too high may cause delayed sensor response

//***********************************************************

int knockAve = 0; 
int readings[numReadings]; 
int index = 0;
int total = 0;





// the setup routine runs once when you press reset:
void setup()  { 

  //*************************KNOCK >> LED SETUP CODE*************************

  Serial.begin(38400);

  pinMode(led, OUTPUT);


  //***************************SMOOTH SETUP CODE*****************************
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;  

} 



// the loop routine runs over and over again forever:
void loop()  { 

  //****************************SMOOTH LOOP CODE****************************

  total= total - readings[index];         
  readings[index] = analogRead(inputPin); 
  total= total + readings[index];       
  index = index + 1;                    

  if (index >= numReadings)              
    index = 0;                           

  knockAve = total / numReadings;         
  Serial.print("Average Knock Readings: ");
  Serial.println(knockAve);   



  //*************************KNOCK >> LED LOOP CODE*************************

  knockLevel = map(knockAve, knockMin, knockMax, 0, 255);


//different brightness steps defined here
  if (knockLevel == 0){
    Serial.println("NO Knock Detected"); 
  }

  if (knockLevel > 0 && knockLevel < 30){
    ledLevel = 30;
    Serial.println("SLIGHT Knock Detected! LED = 30"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 30 && knockLevel < 60){
    ledLevel = 60;
    Serial.println("SMALL Knock Detected! LED = 60"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 60 && knockLevel < 90){
    ledLevel = 90;
    Serial.println("LOW Knock Detected! LED = 90"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 90 && knockLevel < 120){
    ledLevel = 120;
    Serial.println("MEDIUM Knock Detected! LED = 120"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 120 && knockLevel < 150){
    ledLevel = 150;
    Serial.println("BIG Knock Detected! LED = 150"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 150 && knockLevel < 180){
    ledLevel = 180;
    Serial.println("LARGE Knock Detected! LED = 180"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 180 && knockLevel < 210){
    ledLevel = 210;
    Serial.println("HUGE Knock Detected! LED = 210"); 
    analogWrite(led, ledLevel);
  }

  if (knockLevel > 210){
    ledLevel = 255;
    Serial.println("MASSIVE Knock Detected! LED = MAX"); 
    analogWrite(led, ledLevel);
  }


  Serial.print("Current LED level: ");
  Serial.println(ledLevel);
  Serial.println();
  delay(loopDelay);


}



















