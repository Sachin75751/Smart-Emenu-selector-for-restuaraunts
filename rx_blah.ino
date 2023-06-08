#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins for Bluetooth communication
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetoothSerial.begin(9600); // Set the baud rate for Bluetooth communication
  pinMode(LED_BUILTIN, OUTPUT);

   digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("RX System Ready");

}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(bluetoothSerial.available())
  {
    char val =bluetoothSerial.read();
    Serial.println(val);
    if(val == 'A')
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(val == 'a')
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}