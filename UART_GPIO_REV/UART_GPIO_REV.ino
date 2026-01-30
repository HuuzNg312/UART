#define RX_PIN 2       // Chọn chân số 2 làm chân Nhận (Soft RX)
#define BAUDRATE 9600

// Tính toán thời gian cho 1 bit (tính bằng micro giây)
// Với 9600 baud: 1 bit = 1,000,000 / 9600 approx 104 us
const int BIT_PERIOD = 1000000 / BAUDRATE; 

void setup() {
  pinMode(RX_PIN, INPUT_PULLUP); // Quan trọng: Phải có Pull-up để chân luôn ở mức cao khi nghỉ
  
  // Dùng Serial phần cứng để in kết quả lên màn hình máy tính cho bạn xem
  Serial.begin(9600); 
  Serial.println("He thong san sang!");
}

// --- Hàm Nhận tự viết ---
char UART_Soft_Read() {
  char data = 0;

  // 1. Chờ Start Bit (Chờ chân RX xuống mức 0)
  // Trong video dùng while(digitalRead...) để chờ
  while (digitalRead(RX_PIN) == HIGH); 

  // 2. Đợi 1.5 chu kỳ bit để nhảy vào GIỮA bit dữ liệu đầu tiên (LSB)
  // Tại sao 1.5? 
  // - 1.0 chu kỳ để bỏ qua bit Start
  // - 0.5 chu kỳ để nhảy vào chính giữa bit D0 cho chắc ăn
  delayMicroseconds(BIT_PERIOD + (BIT_PERIOD / 2));

  // 3. Đọc 8 bit dữ liệu
  for (int i = 0; i < 8; i++) {
    // Đọc trạng thái chân RX
    int bitValue = digitalRead(RX_PIN);
    
    // Nếu là bit 1 thì cộng vào biến data (Dùng phép dịch bit >> hoặc cộng trọng số)
    if (bitValue == HIGH) {
      data |= (1 << i); // Dịch bit 1 vào vị trí thứ i
    }
    
    // Đợi hết 1 chu kỳ để nhảy sang giữa bit tiếp theo
    delayMicroseconds(BIT_PERIOD);
  }

  // 4. (Tuỳ chọn) Đợi nốt bit Stop (mức cao) để kết thúc khung truyền
  // delayMicroseconds(BIT_PERIOD); 
  
  return data;
}

void loop() {
  // Gọi hàm tự viết của mình
  char c = UART_Soft_Read();
  
  // In ra Serial Monitor để kiểm tra
  Serial.print("Nhan duoc: ");
  Serial.println(c);
}