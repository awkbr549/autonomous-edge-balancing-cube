 // MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>

const int MPU_addr=0x68;  // I2C address of the MPU-6050
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int16_t AcY, GyX;
//double AvgAX, AvgAY, AvgAZ, AvgGX, AvgGY, AvgGZ;
double AvgAY, AvgGX;
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  
  AvgAY = 0;
  AvgGX = 0;
  
  for (int i = 1; i < 1001; i++) {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 10, true);
    Wire.read(); Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    Wire.read(); Wire.read();
    Wire.read(); Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    
    
    AvgAY = ((AvgAY * (i - 1)) + AcY) / i;
    AvgGX = ((AvgGX * (i - 1)) + GyX) / i;
  } //for i
  
  AvgAY = (int)(AvgAY + 0.5);
  AvgGX = (int)(AvgGX + 0.5);
  
  Serial.println("Averages:");
  Serial.println(AvgAY);
  Serial.println(AvgGX);
  Serial.println("Setup complete.");
  Serial.flush();
  
  digitalWrite(LED_BUILTIN, HIGH);
  
  delay(1000);
} //setup

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 10, true);
  Wire.read(); Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();
  Wire.read(); Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  
  Serial.println("::RAW::");
  Serial.print("\t| AcY = "); Serial.print(AcY);
  Serial.print("\t| GyX = "); Serial.print(GyX);
  
  Serial.println();
  Serial.println("::ADJUSTED::");
  Serial.print("\t| AcY = "); Serial.print(AcY - AvgAY);
  Serial.print(" | GyX = "); Serial.print(GyX - AvgGX);
  Serial.println();
  Serial.println();
  delay(1000);
} //setup
