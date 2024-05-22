#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

#include <Servo.h>
Servo servo1;
const int trigPin = 12;
const int echoPin = 11;
long duration;
int distance=0;
int potPin = A0; 
int soil=0;
int fsoil;
void setup() 
{
  Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.clear();
   lcd.print("Skynet Robotics");
   delay(3000);
   Serial.print("Humidity");
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  servo1.attach(8);
}
int readSensor()
{
  int sensorValue=analogRead(sensorPin);
  int outputValue=map(sensorValue,0,1023,255,0);
  analogWrite(ledPin,outputValue);
  return outputValue;
}
void loop() 
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Dry Wet Waste");
  lcd.setCursor(3,1);
  lcd.print("Segregator");
  int soil=0;
  for(int i=0;i<2;i++)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(7);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2+distance;
    delay(10);
  }
  distance=distance/2;
  Serial.println(distance);
  if (distance <15 && distance>1)
  {
    delay(1000);
  for(int i=0;i<3;i++)
  {
    soil = analogRead(potPin) ;
    soil = constrain(soil, 485, 1023);
    fsoil = (map(soil, 485, 1023, 100, 0))+fsoil;
    delay(75);
  }
  fsoil=fsoil/3;
  Serial.println(fsoil);
  Serial.print("%");
  if(fsoil>3)
  {
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Garbage Detected!");
    lcd.setCursor(6,1);
    lcd.print("WET");
    Serial.print("wet");
    servo1.write(180);
    delay(3000);} 
  else
  { 
    delay(1000);
    Serial.print("dry ");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Garbage Detected!");
    lcd.setCursor(6,1);
    lcd.print("DRY");
    servo1.write(0);
    delay(3000);}
    servo1.write(96);
  }
  distance=0;
  fsoil=0;
  delay(1000);
}