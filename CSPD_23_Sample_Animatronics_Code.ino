#include <Wire.h>
#include <Servo.h>

//CSPD Week 2023, Demo Arduino Animatronics
//Dalton Fowler

int trig = 3; // attach pin 3 to Trig
int echo = 4; //attach pin 4 to Echo
int ledPin = 2; //attach LED to 2, 220 ohm resistor 
Servo motor; //create a servo named motor

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  motor.attach(5); //Servo in digital 5!!
  pinMode(ledPin, OUTPUT); //set ledPin to OUTPUT
  pinMode(trig, OUTPUT); //set range sensor trig to OUTPUT
  pinMode(echo, INPUT); //set range sensor echo to INPUT
}

void loop()
{

  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  //print out readings from transducer/range sensor
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

  if (inches >= 20) //if distance is greater than 10 inches
  {
    motor.write(0);
    digitalWrite(ledPin, LOW); //LED off, motor move
    
  }
  if (inches < 20 && inches > 10) //if distance is greater than 10 inches
  {
    motor.write(90);
    digitalWrite(ledPin, HIGH); //LED on, motor move
  }
  if (inches <= 10 ) //if distance is greater than 10 inches
  {
    motor.write(180);
    digitalWrite(ledPin, LOW); //LED off, motor move
  }


}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING, there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}