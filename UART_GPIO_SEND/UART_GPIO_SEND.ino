// --- Định nghĩa các Macro và Chân kết nối ---
// Sử dụng chân số 4 trên Arduino (tương ứng bit 4 của Port D trên ATmega328P)
#define TX_PIN 4 

// Macro cấu hình chân TX là OUTPUT (tác động vào thanh ghi DDRD)
// Dịch bit 1 sang trái 4 lần (tương ứng vị trí PD4) và OR vào DDRD
#define TX_OUTPUT  (DDRD |= (1 << 4))

// Macro ghi mức logic ra chân TX (tác động vào thanh ghi PORTD)
// Nếu x là true (khác 0) -> set bit 4 của PORTD lên 1 (HIGH)
// Nếu x là false (bằng 0) -> clear bit 4 của PORTD về 0 (LOW)
#define WRITE_TX(x) ( (x) ? (PORTD |= (1 << 4)) : (PORTD &= ~(1 << 4)) )

// --- Biến toàn cục ---
unsigned int UART_CYCLE = 0; // Biến lưu thời gian delay cho mỗi bit (chu kỳ bit)

// --- Hàm khởi tạo UART ---
void UART_Begin(unsigned long baud) {
  // Tính toán chu kỳ cho mỗi bit (đơn vị: micro giây)
  // Công thức: 1 giây / baud_rate * 1,000,000
  UART_CYCLE = 1000000 / baud; 

  // Cấu hình chân TX là Output
  TX_OUTPUT;

  // Đặt trạng thái ban đầu là mức cao (IDLE state của UART là mức cao)
  WRITE_TX(1);
}

// --- Hàm gửi 1 Byte dữ liệu (UART Send Byte) ---
void UART_Write(unsigned char byteOut) {
  // 1. Gửi Start Bit (Mức thấp - Low)
  WRITE_TX(0);
  delayMicroseconds(UART_CYCLE); // Chờ hết thời gian 1 bit

  // 2. Gửi 8 Bit dữ liệu (LSB First - Bit thấp gửi trước)
  for (int i = 0; i < 8; i++) {
    // Lấy giá trị bit thấp nhất hiện tại (bit 0)
    unsigned char bit = byteOut & 0x01; 
    
    // Ghi giá trị bit ra chân TX
    WRITE_TX(bit);
    
    // Dịch phải dữ liệu để đưa bit tiếp theo xuống vị trí bit 0
    byteOut >>= 1;
    
    // Chờ hết thời gian 1 bit
    delayMicroseconds(UART_CYCLE);
  }

  // 3. Gửi Stop Bit (Mức cao - High)
  WRITE_TX(1);
  delayMicroseconds(UART_CYCLE); // Chờ hết thời gian stop bit
  
  // (Tùy chọn) Đảm bảo giữ mức cao sau khi kết thúc để về trạng thái IDLE
  WRITE_TX(1); 
}

// --- Chương trình chính ---

void setup() {
  // Khởi tạo UART mềm với tốc độ Baud 9600
  // Lưu ý: Cần delay một chút trước khi khởi tạo để hệ thống ổn định
  delay(100); 
  UART_Begin(9600);
}

void loop() {
  // Vòng lặp gửi các ký tự từ 'a' đến ...
  static char c = 'a'; // Biến static để giữ giá trị qua các lần lặp, hoặc dùng biến toàn cục

  UART_Write(c); // Gửi ký tự
  
  c++; // Tăng ký tự lên (a -> b -> c ...)
  if (c > 'z') c = 'a'; // Reset về 'a' nếu vượt quá (tùy chỉnh)

  delay(1000); // Gửi mỗi giây 1 lần để dễ quan sát
}