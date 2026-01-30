//Định nghĩa chân Rx và Tx cho Serial 2
#define Rx2 12
#define Tx2 13

#define GPS_BAUD 9600

HardwareSerial gpsSerial(2); //tạo tên quản lý cổng UART số 2

void setup(){
  Serial.begin(115200); //khởi tạo Serial monitor

  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, Rx2, Tx2); //khởi tạo 
  Serial.println("Serial 2 started at 9600 baud rate");

}

void loop(){
  while(gpsSerial.available()){
    char c = gpsSerial.read();
    Serial.print(c);
  }
  delay(1000);
  Serial.println("-------------------------------");
}