void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

int oldV;

void loop() {
  // Light ( 2 sensors )
  int valoareIluminare1 = analogRead(2);
  int valoareIluminare2 = analogRead(3);
  Serial.print("Iluminare 1: ");
  Serial.println(valoareIluminare1, DEC);
  Serial.print("Iluminare 2: ");
  Serial.println(valoareIluminare2, DEC);

  digitalWrite(5, HIGH);
  delay(100);
  digitalWrite(5, LOW);
  delay(1000);

  // Temperature
  float temperatura = readTempInCelsius(10,1);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("  ");
  Serial.write(176);
  Serial.println("C");

  digitalWrite(6, HIGH);
  delay(100);
  digitalWrite(6, LOW);
  delay(1000);

  // Umidity
  int v = analogRead(0);
  v = smooth(v, 0.99, oldV);
  oldV = v;
  Serial.print("Umiditate: ");
  Serial.println(v);
  Serial.println();
  
  digitalWrite(7, HIGH);
  delay(100);
  digitalWrite(7, LOW);
  delay(1000);
  
  delay(1000);
}

float readTempInCelsius(int count, int pin) {
  float temperaturaMediata = 0;
  float sumaTemperatura = 0;
  for (int i =0; i < count; i++) {
    int reading = analogRead(pin);
    float voltage = reading * 5.0;
    voltage /= 1024.0;
    float temperatureCelsius = (voltage - 0.5) * 100 ;
    sumaTemperatura = sumaTemperatura + temperatureCelsius;
  }
  return sumaTemperatura / (float)count;
}

int smooth(int data, float filterVal, float smoothedVal)
{
  if(filterVal > 1)
  {
    filterVal = 99;
  }
  else
    if (filterVal <= 0)
    {
      filterVal = 0;
    }
  smoothedVal = (data *(1 - filterVal)) + (smoothedVal * filterVal);

  return (int)smoothedVal;
}

