//define UART pins
#define TXD2 19 
#define RXD2 21 

HardwareSerial mySerial(2); // Use Serial2 for UART communication

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);  // UART setup
  
  Serial.println("ESP32 UART Receiver");
}

void loop() {
  if(mySerial.available()){
    //Read data and display
    String message = mySerial.readStringUntil('\n'); 
    Serial.println("Received: " + message);
  }
}