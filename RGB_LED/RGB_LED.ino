void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5, 255);
  digitalWrite(6, 100);
  digitalWrite(10, 255);

  delay(1000);
}
