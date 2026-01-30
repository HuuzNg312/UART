#include <SoftwareSerial.h>

// Định nghĩa lại chân TXD1, RXD1 
#define TXD1 4 
#define RXD1 2 

SoftwareSerial mySerial(RXD1, TXD1); 

int counter = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); 
  
  Serial.println("ESP32 UART Transmitter"); 
}

void loop(){
  mySerial.println(String(counter));

  Serial.println("Sent: " + String(counter));

  counter++;
  delay(1000);
}