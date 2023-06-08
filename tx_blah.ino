#define button 2
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins for Bluetooth communication

int value=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  bluetoothSerial.begin(9600); // Set the baud rate for Bluetooth communication
 digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("tx sM READY");

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(button);
  if(val == 1 && value == 0)
  {
     bluetoothSerial.println("A");
    Serial.println("A");
    value = 1;
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if(val == 0 && value == 1)
  {
    bluetoothSerial.println("a");
     Serial.println("a");
    value = 0;
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(200);
}