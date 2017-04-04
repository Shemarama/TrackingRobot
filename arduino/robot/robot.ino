#include <Servo.h>

#define  servomaxx   180   // max degree servo horizontal (x) can turn
#define  servomaxy   180   // max degree servo vertical (y) can turn
#define  screenmaxx   640   // max screen horizontal (x)resolution
#define  screenmaxy   480    // max screen vertical (y) resolution
#define  servocenterx   90  // center po#define  of x servo
#define  servocentery   90  // center po#define  of y servo
#define  servopinx   9   // digital pin for servo x
#define  servopiny   10  // digital pin for servo y
#define  baudrate 57600  // com port speed. Must match your C++ setting
#define distancex 1  // x servo rotation steps
#define distancey 1  // y servo rotation steps
#define  screencenterx 210 // x coord of screen center
#define  screencentery 320 // y coord of screen center

int valx = 0;       // store x data from serial port
int valy = 0;       // store y data from serial port
int posx = 76;
int posy = 90;
int incx = 10;  // significant increments of horizontal (x) camera movement
int incy = 10;  // significant increments of vertical (y) camera movement

Servo servox;
Servo servoy;

int LED = 13;

char incomingByte;

void setup() {
  Serial.begin(baudrate);        // connect to the serial port

  pinMode(LED, OUTPUT);         // declare the LED's pin as output
  pinMode(servopinx,OUTPUT);    // declare servox's pin as output
  pinMode(servopiny,OUTPUT);    // declare servoy's pin as output

  servoy.attach(servopiny); 
  servox.attach(servopinx); 
  delay(100);
  servox.write(posx);
  delay(2000);
}

void loop () {
  while(Serial.available() <=0); // wait for incoming serial data
  if (Serial.available() >= 8)  // wait for 4 bytes. 
  {
    valx = 0;
    while(true) {
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;
      valx *= 10;
      valx = ((incomingByte-'0')+valx);
    }

    valy = 0;
    while(true) {
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;
      valy *= 10;
      valy = ((incomingByte-'0')+valy);
    }
    
    
    if ( (posx < (180-4)) && (valx < 290) ) {
      posx += 3;
      servox.write(posx);
      delay(10);
    }
    else if ( (posx > (0+4)) && (valx > 350) ) {
      posx -= 3;
      servox.write(posx);
      delay(10);
    }
    /*
    if (valy < 120) {
      servoy.write(180);
      delay(10);
    }
    else if (valy > 160) {
      servoy.write(0);
      delay(10);
    }*/

    if ( (290 < valx) && (valx < 350) && (210 < valy) && (valy < 270) ) {
      digitalWrite(LED, HIGH);
      delay(5);
    }
    else {
      digitalWrite(LED, LOW);
      delay(5);
    }
  }
}














