//Variables
int thermistorValue;
int pressureValue;
int countStart = 1;
int count;

float voltage;
float temp;
float pressure;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Timer
  count = countStart ++ ;1; 

  //Temperature - Analog to Voltage
  thermistorValue = analogRead(A0);
  voltage = thermistorValue * (5.0/1023.0);

  //Temperature - Voltage to Celsius 
  temp = (voltage * -22.759) + 54.269;

  //Pressure - hPa
  pressureValue = analogRead(A1);
  pressure = ((pressureValue/1024.0)+0.095)/0.0009;

  Serial.print("KCC");
  Serial.print(",");
  Serial.print(count);
  Serial.print(",");
  Serial.print("T");
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print("P");
  Serial.print(",");
  Serial.println(pressure);
  delay(250);
}
