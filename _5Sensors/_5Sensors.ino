#define LIGHT1_PIN 0
#define LIGHT2_PIN 1
#define TEMPERATURE_PIN 2
#define HUMIDITY_PIN 3
#define TRIG_PIN 7
#define ECHO_PIN 8
#define MAX_DIST 23200

int oldV;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  // **************************************************************
  // Light ( 2 sensors )
  int valoareIluminare1 = analogRead(LIGHT1_PIN);
  int valoareIluminare2 = analogRead(LIGHT2_PIN);
  Serial.print("Iluminare 1: ");
  Serial.println(valoareIluminare1, DEC);
  Serial.print("Iluminare 2: ");
  Serial.println(valoareIluminare2, DEC);
  // **************************************************************
  
  // **************************************************************
  // Temperature
  float temperatura = readTempInCelsius(10,TEMPERATURE_PIN);
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("  ");
  Serial.write(176);
  Serial.println("C");
  // **************************************************************

  // **************************************************************
  // Humidity
  int v = analogRead(HUMIDITY_PIN);
  v = smooth(v, 0.99, oldV);
  oldV = v;
  Serial.print("Umiditate: ");
  Serial.println(v);
  
  // **************************************************************
  
  // **************************************************************
  // Ultra Sonic HC_SR04
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;
  
  // Hold the trigger pin high for at least 10 ms
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  
  pulse_width = t2 - t1;
  cm = pulse_width / 58.0;
  inches = pulse_width / 148.0;

  if ( pulse_width > MAX_DIST ) 
    Serial.println("Out of range"); 
  else 
  {
    Serial.print(cm);
    Serial.print(" cm \t");
    Serial.print(inches);
    Serial.println(" in");
  }
  // **************************************************************

  Serial.println();
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
