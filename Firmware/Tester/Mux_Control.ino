#define MUX_ADDR 0x70 //7-bit unshifted default I2C Address

//Enables a specific port number
boolean enableMuxPort(byte portNumber)
{
  //Read the current mux settings
  Wire.requestFrom(MUX_ADDR, 1);
  if(Wire.available() == 0) return(false);
  byte settings = Wire.read();

  //Set the wanted bit to enable the port
  settings |= (1 << portNumber);

  Wire.beginTransmission(MUX_ADDR);
  Wire.write(settings);
  Wire.endTransmission();
  return(true);
}

boolean disableMuxPort(byte portNumber)
{
  //Read the current mux settings
  Wire.requestFrom(MUX_ADDR, 1);
  if(Wire.available() == 0) return(false);
  byte settings = Wire.read();

  //Clear the wanted bit to disable the port
  settings &= ~(1 << portNumber);

  Wire.beginTransmission(MUX_ADDR);
  Wire.write(settings);
  Wire.endTransmission();
  return(true);
}
