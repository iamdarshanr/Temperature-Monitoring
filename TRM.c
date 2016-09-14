int t=0;
int vcc=A0; // sets analog input A0 as +5V source for LM35
int sensor=A1; // sets A1 as the sensor input
int gnd=A2; // sets analog input A2 as ground for LM35
float temp;
int tempc;
float tempf;
void setup()
{
  pinMode(vcc,OUTPUT);
  pinMode(gnd,OUTPUT);
  pinMode(sensor,INPUT);
  digitalWrite(vcc,HIGH); // sets analog input A0 HIGH
  digitalWrite(gnd,LOW);  // sets analog input A2 LOW
  Serial.begin(9600);     // sets the baud rate at 9600

}
void loop()
{ delay(2000); // calls a 2 second delay
  t=t+2;       // increments the time by 2 every two seconds
  temp=analogRead(sensor); // reads the LM35 output
  tempc=(temp*5)/10;       // converts the digital value into temperature degree C
  tempf=(tempc*1.8)+32;    // converts degree C to degree F
  Serial.println("...............");
  Serial.println("Temperature logger");
  Serial.print("Temperature in deg C = "); // prints the temperature in degreeC
  Serial.println(tempc);
}