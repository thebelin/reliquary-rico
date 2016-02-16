/* 
   The circuit:
    * +V connection of the PING & PING2))) attached to +5V
    * GND connection of the PING & PING2))) attached to ground
    * SIG connection of the PING))) attached to digital pin 7
    * SIG connection of PING2))) attached to digital pin 8
    * LED+ on Pin 5, LED- to ground

 */

// this constant won't change.  It's the pin number
// of the sensor's output:
const int pingPin = 7;
const int ping2Pin = 8;

// This is where the LED is connected
const int ledPin = 5;

// The maximum range (in cm) to start the light at
const int maxRange = 300;

// The minimum range (in cm) where the light will be most bright
const int minRange = 6;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, duration2, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);


  // The PING2))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(ping2Pin, OUTPUT);
  digitalWrite(ping2Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(ping2Pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(ping2Pin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ping2Pin, INPUT);
  duration2 = pulseIn(ping2Pin, HIGH);

  // If duration2 is closer than duration, use it for duration
  if (duration2 < duration) {
    duration = duration2;
  }
  
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // Light up the light according to the distance
  // It should become more bright as the ping approaches
  analogWrite(ledPin, map(cm, minRange, maxRange, 0, 255));

  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
