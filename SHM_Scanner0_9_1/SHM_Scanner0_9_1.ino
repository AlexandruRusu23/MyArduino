unsigned long serialData;
int inByte;
int digitalState;
int pinNumber;
int analogRate;
int sensorVal;

void setup()
{
  Serial.begin(9600);
}

void loop()
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
          Serial.println("Analog write");
          // analog write
          getSerial();
          pinNumber = serialData;
          getSerial();
          analogRate = serialData;
          pinMode(pinNumber, OUTPUT);
          analogWrite(pinNumber, analogRate);
          pinNumber = 0;
          break;
        }
        case 2:
        {
          Serial.println("Digital write!");
          //digital write
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
            digitalWrite(pinNumber, 0);
          }
          if (digitalState == 1)
          {
            Serial.println("Turn ON!");
            digitalWrite(pinNumber, 255);
          }
          pinNumber = 0;
          break;
        }
      }
      break;
    }
    case 2:
    {
      getSerial();
      switch (serialData)
      {
      case 1:
        {
          //analog read
          getSerial();
          pinNumber = serialData;
          pinMode(pinNumber, INPUT);
          sensorVal = analogRead(pinNumber);
          Serial.println(sensorVal);
          sensorVal = 0;
          pinNumber = 0;
          break;
        } 
      case 2:
        {
          //digital read
          getSerial();
          pinNumber = serialData;
          pinMode(pinNumber, INPUT);
          sensorVal = digitalRead(pinNumber);
          Serial.println(sensorVal);
          sensorVal = 0;
          pinNumber = 0;
          break;
        }
      }
      break;
    }
  }
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

