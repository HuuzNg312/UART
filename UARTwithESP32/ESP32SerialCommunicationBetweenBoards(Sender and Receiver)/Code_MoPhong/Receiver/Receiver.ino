#include <SoftwareSerial.h>

// Định nghĩa chân RXD2, TXD2 
#define TXD2 4 
#define RXD2 2 


SoftwareSerial mySerial(RXD2, TXD2); 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); 
  
  Serial.println("ESP32 UART Receiver"); 
}

void loop() {
  if(mySerial.available()){ 
    
    String message = mySerial.readStringUntil('\n');
    Serial.println("Received: " + message);
  }
}