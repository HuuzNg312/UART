//define TX and Rx pins
#define TXD1 19 
#define RXD1 21 

HardwareSerial mySerial(1); //Use Serial1 for UART communication

int counter = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXD1, TXD1);  // UART setup
  
  Serial.println("ESP32 UART Transmitter");
}

void loop(){
  //Send message over UART
  mySerial.println(String(counter));

  Serial.println("Sent: " + String(counter));

  counter++;
  delay(1000);
}