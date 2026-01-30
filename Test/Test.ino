void setup() {
  // Khởi động cổng kết nối Serial với tốc độ 9600 bit/giây.
  // Lưu ý: Tốc độ này phải khớp với cài đặt trong Serial Monitor.
  Serial.begin(9600); 
  Serial.println("He thong da san sang!"); //Gửi thông báo đầu tiên
}

void loop() {
    //put your main code here, to run repeatedly:
    if(Serial.available() > 0) // it will only send data when the received data is greater than 0.
    {
      String data = Serial.readString(); // Đọc ký tự nhận được
      Serial.print("Ban vua nhap: ");
      Serial.println(data);
    }
    delay(10);
}