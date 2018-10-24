 // MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double AvgAX, AvgAY, AvgAZ, AvgGX, AvgGY, AvgGZ;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  
  AvgAX = 0;
  AvgAY = 0;
  AvgAZ = 0;
  AvgGX = 0;
  AvgGY = 0;
  AvgGZ = 0;
  
  for (int i = 1; i < 1001; i++) {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    Wire.read(); Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();
    Wire.endTransmission(true);
    
    
    AvgAX = ((AvgAX * (i - 1)) + AcX) / i;
    AvgAY = ((AvgAY * (i - 1)) + AcY) / i;
    AvgAZ = ((AvgAZ * (i - 1)) + AcZ) / i;
    AvgGX = ((AvgGX * (i - 1)) + GyX) / i;
    AvgGY = ((AvgGY * (i - 1)) + GyY) / i;
    AvgGZ = ((AvgGZ * (i - 1)) + GyZ) / i;
    
    //Serial.println(i);
  } //for i
  
  AvgAX = (int)(AvgAX + 0.5);
  AvgAY = (int)(AvgAY + 0.5);
  AvgAZ = (int)(AvgAZ + 0.5);
  AvgGX = (int)(AvgGX + 0.5);
  AvgGY = (int)(AvgGY + 0.5);
  AvgGZ = (int)(AvgGZ + 0.5);
  
  Serial.println("Averages:");
  Serial.println(AvgAX);
  Serial.println(AvgAY);
  Serial.println(AvgAZ);
  Serial.println(AvgGX);
  Serial.println(AvgGY);
  Serial.println(AvgGZ);
  
  delay(1000);
  
  Serial.println("Setup complete.");
  
  delay(1000);
} //setup

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Wire.endTransmission(true);
  Serial.println("::RAW::");
  //Serial.print("AcX = "); Serial.print(AcX);
  Serial.print("\t| AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print("\t| GyX = "); Serial.print(GyX);
  //Serial.print(" | GyY = "); Serial.print(GyY);
  //Serial.print(" | GyZ = "); Serial.println(GyZ);
  
  Serial.println();
  Serial.println("::ADJUSTED::");
  
  //Serial.print("AcX = "); Serial.print(AcX - AvgAX);
  Serial.print("\t| AcY = "); Serial.print(AcY - AvgAY);
  //Serial.print("\t| AcZ = "); Serial.print(AcZ - AvgAZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX - AvgGX);
  //Serial.print("\t| GyY = "); Serial.print(GyY - AvgGY);
  //Serial.print(" | GyZ = "); Serial.println(GyZ - AvgGZ);
  Serial.println();
  Serial.println();
  delay(1000);
} //setup
