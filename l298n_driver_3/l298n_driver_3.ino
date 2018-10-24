int dir1 = 7;
int dir2 = 8;
int pwm = 9;

void setup() {
  Serial.begin(115200);
  
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm, OUTPUT);
  
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  digitalWrite(pwm, LOW);
  
  Serial.println("Setup compelte.");
} //setup

void loop() {
  if (Serial.available() > 0) {
    int motor = Serial.parseInt();
    int speed = Serial.parseInt();
    Serial.println(speed);
    
    analogWrite(pwm, speed);
    if (motor == 1) {
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, HIGH);
    } else {
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);
    } //if-else
    
  } //if
  delay(10);
} //loop
