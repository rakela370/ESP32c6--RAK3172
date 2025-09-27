
HardwareSerial RAK(1);  //UART1

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32C6 UART test start...");

  //PINS: RX=4, TX=5
  RAK.begin(115200, SERIAL_8N1, 4, 5);

  delay(1000);
  Serial.println("Saljem AT...");
  RAK.println("AT");
}

void loop() {
  while (RAK.available()) {
    char c = RAK.read();
    Serial.write(c); // prikazi odgovor iz RAK-a
  }

  // periodično šalji AT svake 3 sekunde
  static unsigned long lastSend = 0;
  if (millis() - lastSend > 3000) {
    RAK.println("AT");
    Serial.println("Ponovo poslat AT");
    lastSend = millis();
  }
}


