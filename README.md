## 📡 Giao thức UART (Universal Asynchronous Receiver-Transmitter)

UART là giao thức truyền thông nối tiếp không đồng bộ, cho phép trao đổi dữ liệu song công (Full-Duplex) giữa các thiết bị vi điều khiển và ngoại vi mà không cần tín hiệu Clock đồng bộ chung.

### 🛠 Thông số kỹ thuật (Technical Specifications)

Để giao tiếp thành công, cả hai thiết bị (Transmitter & Receiver) phải được cấu hình đồng nhất các tham số sau:

| Tham số | Giá trị phổ biến | Mô tả chi tiết |
| :--- | :--- | :--- |
| **Baud Rate** | `9600`, `115200` | Tốc độ truyền dữ liệu (bit per second). Thời gian của 1 bit = `1/BaudRate`. |
| **Data Bits** | `8 bits` | Số lượng bit dữ liệu thực tế trong một gói tin (thường là 5, 6, 7, 8 hoặc 9 bit). |
| **Parity Bit** | `None` | Bit kiểm tra lỗi: None (Không), Even (Chẵn), hoặc Odd (Lẻ). |
| **Stop Bits** | `1 bit` | Bit báo hiệu kết thúc khung truyền (1, 1.5, hoặc 2 bits). |
| **Flow Control**| `None` | Kiểm soát luồng dữ liệu (Hardware CTS/RTS hoặc Software XON/XOFF). |
| **Logic Level** | `TTL` (3.3V/5V) | Mức điện áp hoạt động (Lưu ý: Khác với chuẩn RS-232 mức ±12V). |

### 📦 Cấu trúc khung dữ liệu (Data Frame Structure)

Dữ liệu được truyền nối tiếp theo thứ tự thời gian như sau (từ trái sang phải):

`[Start Bit]` ➡️ `[Data Bits (LSB First)]` ➡️ `[Parity Bit]` ➡️ `[Stop Bit]`

1.  **Idle State (Trạng thái nghỉ):** Đường truyền giữ ở mức điện áp cao (Logic 1 / High) khi không có dữ liệu.
2.  **Start Bit:** Thiết bị gửi kéo đường truyền xuống mức thấp (Logic 0) trong thời gian 1 bit để đánh thức thiết bị nhận.
3.  **Data Bits:** Dữ liệu chính được gửi đi, thường bắt đầu từ Bit có trọng số thấp nhất (LSB - Least Significant Bit) đến Bit trọng số cao nhất (MSB).
4.  **Parity Bit (Tùy chọn):** Nếu được kích hoạt, bit này dùng để kiểm tra tính toàn vẹn của dữ liệu (check lỗi).
5.  **Stop Bit:** Đường truyền được kéo lên mức cao (Logic 1) để báo hiệu kết thúc gói tin và đưa đường truyền trở về trạng thái nghỉ hoặc chuẩn bị cho gói tin tiếp theo.

### 🔌 Nguyên lý đấu nối (Hardware Interface)

Giao thức UART yêu cầu đấu nối chéo (Cross-connection) giữa hai thiết bị:

* **TX (Transmit):** Chân truyền dữ liệu.
* **RX (Receive):** Chân nhận dữ liệu.

**Sơ đồ kết nối:**
* `TX` (Device A) nối với `RX` (Device B)
* `RX` (Device A) nối với `TX` (Device B)
* `GND` nối với `GND` (Bắt buộc để tham chiếu mức điện áp chung)