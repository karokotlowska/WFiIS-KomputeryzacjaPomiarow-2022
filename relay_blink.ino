
#include <Wire.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 mpl115a2;

const int ledPin =  7;

char input;

int ledState = LOW;            

unsigned long previousMillis = 0;       

const long interval = 300;          

unsigned long startTime;

float p = 50.0;

void setup() {
  startTime = millis();
  
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

   if (! mpl115a2.begin()) {
    Serial.println("Sensor not found! Check wiring");
    while (1);
  }
}

void loop() {

  unsigned long currentMillis = millis();
  unsigned long deltaMillis = currentMillis - startTime;

  double timeSec = double(deltaMillis)/10000.0;

  float temperatureC = 0;    

  temperatureC = mpl115a2.getTemperature();  

  Serial.print(temperatureC, 1);
  Serial.print("#");

  
  while (Serial.available()) {
    input = Serial.read();
    
    p = (float)input; 
  }
  if((timeSec-floor(timeSec))*100.0 > p){
          ledState = HIGH; 
  } else {
          ledState = LOW;
  }
  Serial.println(!ledState, 1);
  
   digitalWrite(ledPin, ledState);
   Serial.flush();
   delay(500);
}
