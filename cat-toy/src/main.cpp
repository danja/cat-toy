#include <Arduino.h>
#include <Servo.h> //including the servo library

Servo sg90; //including a variable for servo named sg90
int servo_pin = 2;

int LED = 13;          // Use the onboard Uno LED
int isObstaclePin = 3; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE

void setup()
{
  sg90.attach(servo_pin);
  pinMode(LED, OUTPUT);
  pinMode(isObstaclePin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  /*
  sg90.write(0);     // moving the servo at 0 degree
  delay(1000);
  sg90.write(45);     // moving the servo at 45 degree
  delay(1000);
  sg90.write(90);    // moving the servo at 90 degree
  delay(1000);        // wait for 1 second
  sg90.write(135);     // moving the servo at 135 degree
  delay(1000);
  sg90.write(180);   // moving the servo at 180 degrees
  delay(1000);        // wait for 1 sec
*/
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)
  {
    Serial.println("OBSTACLE!!, OBSTACLE!!");
    sg90.write(180); // moving the servo at 180 degrees
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("clear");
    sg90.write(0); // moving the servo at 0 degree
    digitalWrite(LED, LOW);
  }
  delay(200);
}