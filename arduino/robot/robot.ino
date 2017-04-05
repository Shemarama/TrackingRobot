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
#define  screencenterx 320 // x coord of screen center
#define  screencentery 240 // y coord of screen center

int valx = 0;       // store x data from serial port
int valy = 0;       // store y data from serial port
int posx = 74;
int posy = 30;
int incx = 10;  // significant increments of horizontal (x) camera movement
int incy = 10;  // significant increments of vertical (y) camera movement
int dx = 0;
int dy = 0;
int scalex = 15;
int scaley = 22;

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
  servoy.write(posy);
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
    
    
    if ( (posx < (180)) && (valx < 290) ) {
      dx = int((screencenterx-valx)/scalex);
      posx += dx;
      if (posx > 180)
        posx = 180;
      servox.write(posx);
      delay(10);
    }
    else if ( (posx > (0)) && (valx > 350) ) {
      dx = int((screencenterx-valx)/scalex);
      posx += dx;
      if (posx < 0)
        posx = 0;
      servox.write(posx);
      delay(10);
    }

    if ( (posy < (180)) && (valy < 210) ) {
      dy = int((screencenterx-valy)/scaley);
      posy += dy;
      if (posy > 180)
        posy = 180;
      servoy.write(posy);
      delay(10);
    }
    else if ( (posy > (0)) && (valy > 270) ) {
      dy = int((screencentery-valy)/scaley);
      posy += dy;
      if (posy < 0)
        posy = 0;
      servoy.write(posy);
      delay(10);
    }

    

    if ( (290 < valx) && (valx < 350) && (210 < valy) && (valy < 270) )
      digitalWrite(LED, HIGH);
    else
      digitalWrite(LED, LOW);
    delay(5);
  }
}














