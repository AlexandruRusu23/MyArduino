void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = 0;
  int valoareButon = digitalRead(11);
  if(valoareButon == 1)
    if(state == 10)
      state = 0;
    else
      state = 100;

  for(int i=7; i<=10; i++)
  {
    digitalWrite(i, state);
  }
}
