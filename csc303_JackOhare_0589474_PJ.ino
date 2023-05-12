//Jack OHare
//0589474
//jmohare@cn.edu
#define echoPin A0
#define trigPin A1
int duration;
int cm;
int dist;

//BLUETOOTH
#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13);
bool alarmActive = true;

//7 DIGIT
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;

void dig_Off( )
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);

}

void dig_On( )
{
digitalWrite(a, HIGH);
digitalWrite(b, HIGH);
digitalWrite(c, HIGH);
digitalWrite(d, HIGH);
digitalWrite(e, HIGH);
digitalWrite(f, HIGH);
digitalWrite(g, LOW);
}


//PROTOTYPES
int detectPulse(int delayedTime);


void setup() {
  //BLUETOOTH
  mySerial.begin(9600);
  Serial.begin(9600);

  //7 DIGIT
  for (int i = a; i <= g; i++)
  {
    pinMode(i, OUTPUT);
  }

  //SENSOR
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //bluetooth check for if to set alarm active
    activeCheck();
    //ACTIVE
    while (alarmActive)
    {
      //Digit 7 is set O
      dig_On();
      dist = detectPulse(250);

      Serial.println(dist);
      //Pauses for 20 seconds if the distance gets changed. Alert and difference check is done on
      //python part
      if(dist >= 20)
        {
         delay(20000);
        }
      //Done to see if system has been turned on since alert
      activeCheck();
    }
   dig_Off();
}
/*
 * Determintes if the app has been used to turn off or on the alarm system
 * Bluetooth HC-06 in use
 */
void activeCheck()
{
  if (mySerial.available())
  {
    char s = mySerial.read();
    if ( s == 'b')
    {
      //Serial.println("false");
      alarmActive = false;
    }
    else if  ( s == 'a')
    {
      //Serial.println("true");
      alarmActive = true;
    }
  }
}
/*
 * Called in order to check and return the distance between the sensor and door
 * Ultrasonic module in use
 */
int detectPulse(int delayedTime)
{

  //Sensor triggered by a high pulse of 10 or more microseconds
  //give a short low pulse beforehand to ensure a clean high pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //read signal from sensor a high pulse
  // whos duration is the time in microsends from the sending of the ping to the reception
  //of its echo off an object
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;
  delay(delayedTime);
  return cm;

}
