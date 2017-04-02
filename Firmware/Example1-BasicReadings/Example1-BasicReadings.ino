/*
  Qwiic Mux Shield - PCA9548A/TCA9548A Basic Control
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 30th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Reads two MMA8452Q accelerometers that have the same I2C address. You
  can read the hookup guide and get the library from https://learn.sparkfun.com/tutorials/mma8452q-accelerometer-breakout-hookup-guide
  
  Outputs two sets of XYZ

  Hardware Connections:
  Attach the Qwiic Mux Shield to your RedBoard or Uno. 
  Plug two Qwiic MMA8452Q breakout boards into ports 0 and 1.
  
  Serial.print it out at 9600 baud to serial monitor.

*/

#include <Wire.h>
#include <SFE_MMA8452Q.h> // Includes the SFE_MMA8452Q library

#define MUX_ADDR 0x70 //7-bit unshifted default I2C Address

MMA8452Q accel0;
MMA8452Q accel1;

void setup()
{
  Serial.begin(9600);
  Serial.println("Qwiic Mux Shield Read Example");

  Wire.begin();

  
  enableMuxPort(0); //Tell mux to connect to port zero
  accel0.init(); //Turn on sensor
  disableMuxPort(0);

  enableMuxPort(1); //Tell mux to connect to port one
  accel1.init(); //Turn on sensor
  disableMuxPort(1);

  Serial.println("Mux Shield online");
}

void loop()
{
  enableMuxPort(0); //Tell mux to connect to port zero
  if (accel0.available())
  {
    accel0.read();
    
    Serial.print("Accel0: ");
    printCalculatedAccels0();
    //printAccels(); // Uncomment to print digital readings
    
    Serial.println(); // Print new line every time.
  }
  disableMuxPort(0); //Tell mux to disconnect from port zero

  enableMuxPort(1); //Tell mux to connect to port one
  if (accel1.available())
  {
    accel1.read();
    
    Serial.print("Accel1: ");
    printCalculatedAccels1();
    //printAccels(); // Uncomment to print digital readings
    
    Serial.println(); // Print new line every time.
  }
  disableMuxPort(1); //Tell mux to disconnect from port zero

  delay(1); //Wait for next reading
}

//Enables 
void enableMuxPort(byte portNumber)
{
  //Read the current mux settings
  Wire.requestFrom(MUX_ADDR, 1);
  byte settings = Wire.read();

  //Set this bit
  settings |= (1 << portNumber);

  Wire.beginTransmission(MUX_ADDR);
  Wire.write(settings);
  Wire.endTransmission();
}

void disableMuxPort(byte portNumber)
{
  //Read the current mux settings
  Wire.requestFrom(MUX_ADDR, 1);
  byte settings = Wire.read();

  //Clear this bit
  settings &= ~(1 << portNumber);

  Wire.beginTransmission(MUX_ADDR);
  Wire.write(settings);
  Wire.endTransmission();
}

// The function demonstrates how to use the accel.x, accel.y and
//  accel.z variables.
// Before using these variables you must call the accel.read()
//  function!
void printAccels()
{
  Serial.print(accel0.x, 3);
  Serial.print("\t");
  Serial.print(accel0.y, 3);
  Serial.print("\t");
  Serial.print(accel0.z, 3);
  Serial.print("\t");
}

// This function demonstrates how to use the accel.cx, accel.cy,
//  and accel.cz variables.
// Before using these variables you must call the accel.read()
//  function!
void printCalculatedAccels0()
{ 
  Serial.print(accel0.cx, 3);
  Serial.print("\t");
  Serial.print(accel0.cy, 3);
  Serial.print("\t");
  Serial.print(accel0.cz, 3);
  Serial.print("\t");
}

void printCalculatedAccels1()
{ 
  Serial.print(accel1.cx, 3);
  Serial.print("\t");
  Serial.print(accel1.cy, 3);
  Serial.print("\t");
  Serial.print(accel1.cz, 3);
  Serial.print("\t");
}
