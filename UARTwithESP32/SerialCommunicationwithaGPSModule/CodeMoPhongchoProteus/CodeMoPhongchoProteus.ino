#include <TinyGPS.h>

TinyGPS gps;

void setup() {
  Serial.begin(9600);  // Giao tiếp với GPS và Virtual Terminal qua chân 0, 1

  Serial.println("--- GPS MONITORING SYSTEM ---");
  Serial.println("Waiting for satellite data...");
}

void loop() {
  bool newData = false;
  unsigned long startTime = millis();

  // Vòng lặp quét dữ liệu trong 1 giây (1000ms)
  while (millis() - startTime < 1000) {
    while (Serial.available()) {
      char c = Serial.read();
      // Nếu giải mã thành công một gói tin
      if (gps.encode(c)) {
        newData = true;
      }
    }
  }

  // Nếu có dữ liệu mới thì in ra
  if (newData) {
    float lat, lon;
    unsigned long age;

    // Lấy tọa độ từ thư viện
    gps.f_get_position(&lat, &lon, &age);

    Serial.print("LAT: ");
    Serial.print(lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat, 6);
    Serial.print(" | LON: ");
    Serial.println(lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon, 6);
  }
}