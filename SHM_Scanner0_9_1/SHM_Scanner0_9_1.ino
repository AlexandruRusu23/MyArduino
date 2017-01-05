unsigned long serialData;
int inByte;
int digitalState;
int pinNumber;
int analogRate;
int sensorVal;

void setup()
{
  delay(100);
  Serial.begin(9600);
  delay(100);
}

void loop()
{
  CommandManager();
  delay(10);
}

long getSerial()
{
  serialData = 0;
  while(inByte != '/')
  {
    inByte = Serial.read();
    if(inByte > 0 && inByte != '/')
    {
      serialData = serialData * 10 + inByte - '0';
      Serial.println(serialData);
    }
  }

  inByte = 0;
  return serialData;
}

void CommandManager()
{
  getSerial();
  switch(serialData)
  {
    case 1:
    {
      Serial.println("Analog/Digital write");
      //analog digital write
      getSerial();
      switch(serialData)
      {
        case 1:
        {
          AnalogWrite();
          break;
        }
        case 2:
        {
          DigitalWrite();
          break;
        }
      }
      break;
    }
    case 2:
    {
      Serial.println("Analog/Digital read");
      getSerial();
      switch (serialData)
      {
      case 1:
        {
          AnalogRead();
          break;
        } 
      case 2:
        {
          DigitalRead();
          break;
        }
      }
      break;
    }
  }
}

void AnalogRead()
{
  Serial.println("Analog read!");
  getSerial();
  pinNumber = serialData;
  Serial.print("Pin number: ");
  Serial.println(pinNumber);
  pinMode(pinNumber, INPUT);
  sensorVal = analogRead(pinNumber);
  Serial.println(sensorVal);
  sensorVal = 0;
  pinNumber = 0;
}

void AnalogWrite()
{
  Serial.println("Analog write");
  getSerial();
  pinNumber = serialData;
  getSerial();
  analogRate = serialData;
  pinMode(pinNumber, OUTPUT);
  analogWrite(pinNumber, analogRate);
  pinNumber = 0;
}

void DigitalRead()
{
  Serial.println("Digital read");
  getSerial();
  pinNumber = serialData;
  Serial.print("Pin number: ");
  Serial.println(pinNumber);
  pinMode(pinNumber, INPUT);
  sensorVal = digitalRead(pinNumber);
  Serial.println(sensorVal);
  sensorVal = 0;
  pinNumber = 0;
}

void DigitalWrite()
{
  Serial.println("Digital write!");        
  getSerial();
  pinNumber = serialData;
  Serial.print("Pin number: ");
  Serial.println(pinNumber);
  getSerial();
  digitalState = serialData;
  pinMode(pinNumber, OUTPUT);
  if (digitalState == 0)
  {
    Serial.println("Turn OFF!");
    digitalWrite(pinNumber, LOW);
  }
  if (digitalState >= 1)
  {
    Serial.println("Turn ON!");
    digitalWrite(pinNumber, digitalState);
  }
  pinNumber = 0;
}

