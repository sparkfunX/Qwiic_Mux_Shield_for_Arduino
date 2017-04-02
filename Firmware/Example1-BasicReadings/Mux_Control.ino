#define MUX_ADDR 0x70 //7-bit unshifted default I2C Address

//Reads from a give location
byte readRegister(byte location)
{
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(location);
  Wire.endTransmission();

  Wire.requestFrom(MUX_ADDR, 1);

  if (!Wire.available()) return (255);

  return (Wire.read());
}

//Write a value to a spot
void writeRegister(byte location, byte val)
{
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(location);
  Wire.write(val);
  Wire.endTransmission();
}

//Reads a two byte value from a consecutive registers
int readRegister16(byte location)
{
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(location);
  Wire.endTransmission(); //Send a restart command. Do not release bus.

  Wire.requestFrom(MUX_ADDR, 2);

  int data = Wire.read();
  data |= (Wire.read() << 8);

  return (data);
}

