#include <Arduino.h>
#include <Servo.h>

Servo servo;

// hardware config
const int LED = 13; // Onboard LED
const int SERVO_PIN = 2;
const int PROXIMITY_PIN = 3;

const unsigned long INACTIVITY_DELAY = 600000; // 10 minutes
const int MAX_ANGLE_STEP = 30; // max jump for each reaction

unsigned long lastChangeTime = millis();
int proximity = HIGH; // HIGH = no obstacle
int previousProximity = HIGH;
int currentAngle = 90;
int currentDirection = 1; // 1 for increasing angle, -1 for decreasing

// forward declarations of functions
int moveTo(int); // move to given angle
int twitch(int); // random jump
void wave(); // slow move bach & forth

void setup()
{
  // Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(LED, OUTPUT);
  pinMode(PROXIMITY_PIN, INPUT);

  delay(500);
  wave();
}

void loop()
{
  proximity = digitalRead(PROXIMITY_PIN);
  digitalWrite(LED, !proximity);
  if (proximity != previousProximity) // change
  {
    // Serial.print("Change, now : ");
    // Serial.println(proximity);
    servo.write(currentAngle);
    previousProximity = proximity;
    currentAngle = currentAngle + currentDirection * MAX_ANGLE_STEP;
    currentAngle = twitch(currentAngle);
    currentAngle = moveTo(currentAngle);
    lastChangeTime = millis();
  }
  else // no change
  {
    if (millis() - lastChangeTime > INACTIVITY_DELAY)
    {
      wave();
    }
  }
  delay(100);
}

/* 
   Check bounds of current angle,
   (reversing if at extreme)
   and go to it.
   */ 
int moveTo(int currentAngle) 
{
  if (currentAngle > 180)
  {
    currentAngle = 180;
    currentDirection = -currentDirection;
  }
  if (currentAngle < 0)
  {
    currentAngle = 0;
    currentDirection = -currentDirection;
  }
  servo.write(currentAngle);
  return currentAngle;
}

int twitch(int currentAngle)
{
  currentAngle += random(2*MAX_ANGLE_STEP) - MAX_ANGLE_STEP;
  currentAngle = moveTo(currentAngle);
  return currentAngle;
}

void wave()
{
  for (int i = 0; i < 180; i++)
  {
    servo.write(i);
    delay(10);
  }
  currentAngle = twitch(currentAngle);
  for (int i = 180; i > 0; i--)
  {
    servo.write(i);
    delay(10);
  }
  currentAngle = twitch(currentAngle);
  lastChangeTime = millis();
}
