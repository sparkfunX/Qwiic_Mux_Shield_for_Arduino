/*
  Qwiic Mux Shield - Tester
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 30th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Quickly talks to the mux and verifies it can see an MMA8452Q on Port 1.

  Hardware Connections:
  Attach the Qwiic Mux Shield to your RedBoard or Uno.
  Plug one Qwiic MMA8452Q breakout board into port 1.
  Serial.print it out at 9600 baud to serial monitor.

*/

#include <Wire.h>
#include <SFE_MMA8452Q.h> //From: https://github.com/sparkfun/SparkFun_MMA8452Q_Arduino_Library

MMA8452Q accel;

void setup()
{
  Serial.begin(9600);
  Serial.println("Qwiic Mux Tester");
}

void loop()
{
  Wire.begin();

  if (enableMuxPort(1) == true) //Tell mux to connect to port one
  {
    accel.init(); //Turn on sensor

    delay(100); //Wait for next reading

    if (accel.available())
    {
      accel.read();

      Serial.print("MUX GOOD - Accel: ");
      printCalculatedAccels();
      Serial.println(); // Print new line every time.
    }
    else
    {
      Serial.println("No accel detected");
    }
    disableMuxPort(1); //Tell mux to disconnect from port zero
  }
  else
  {
    Serial.println("No MUX detected");
  }

}

void printCalculatedAccels()
{
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}
