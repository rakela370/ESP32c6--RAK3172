# ESP32C6 ↔ RAK3172 UART Test

Ovaj projekat demonstrira kako povezati **ESP32C6** i **RAK3172 LoRa modul** putem UART komunikacije koristeći Arduino IDE.

---

##  Hardverska konekcija

| ESP32C6 Pin | RAK3172 Pin |
|------------|-------------|
| **3V3**    | VCC (3V3)   |
| **GND**    | GND         |
| **GPIO4**  | TXD         |
| **GPIO5**  | RXD         |

>  **Napomena:** Obavezno koristiti napajanje od 3.3V (nikako od 5V)

---

##  Instalacija i Podešavanje

1. Instalirati **Arduino IDE 2.x**. Na starijoj verziji arduino-ide nismo uspjeli flash-ovati kod
2. U `File > Preferences > Additional Board URLs` dodaj:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Instaliraj **esp32 by Espressif Systems** iz Board Manager-a i izaberi **ESP32C6 Dev Module**.
4. Podesi port na `/dev/ttyACM0` 
5. Odaberi baudrate `115200` u Serial Monitoru.

---

##  Kod za konekciju ESP32c6 sa RAK modulom 

```cpp
#include <HardwareSerial.h>

HardwareSerial RAK(1);  // koristimo UART1

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32C6 UART test start...");

  // RX=5, TX=4
  RAK.begin(115200, SERIAL_8N1, 5, 4);

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
```

---

##  Očekivani Ispis

Ako je sve ispravno povezano, u **Serial Monitoru** će se pojaviti:

```
ESP32C6 UART test start...
Saljem AT...
OK
Ponovo poslat AT
OK
...
```

> `OK` dolazi iz RAK3172 modula kao odgovor na `AT` komandu.

---

##  Troubleshooting

- Ako nema ispisa:
  - Proveriti da li je izabran pravi port i baudrate u Arduino IDE-u.
  - Isključiti sve druge programe koji mogu koristiti `/dev/ttyACM0` (npr. drugi Serial Monitor).
  - Resetovati ESP32C6 pločicu i ponovo otvoriti Serial Monitor.
- Ako nema `OK` odgovora:
  - Proveriti TX/RX žice (mogu biti zamenjene).
  - Proveriti da li RAK3172 radi i da li je napajanje je 3.3V.

---

## Proširenje – Ping/Pong Logika

Jednom kada se potvrdi da UART komunikacija radi, možeš implementirati **LoRa Ping/Pong logiku** na sledeći način:

- Jedna pločica (Ping) periodično šalje LoRa poruku (npr. `"PING"`).
- Druga pločica (Pong) odgovara sa `"PONG"` kada primi poruku.
- Na ovaj način se moze meriti latencija i proveravati domet.

Tip: možete dodati jednostavan `#define ROLE_PING` ili `#define ROLE_PONG` na početku koda i pomoću `#ifdef` selektovati logiku za tu pločicu, tako da postoji **jedan jedinstveni kod** koji se razlikuje samo po definiciji u vrhu fajla.

Primer:

```cpp
#define ROLE_PING

void loop() {
#ifdef ROLE_PING
  // šalji PING komande
#else
  // odgovori PONG
#endif
}
```

Ovo olakšava održavanje koda i rad sa više uređaja.

---

 **Autori:** Nikola Rakic i Milos Markovic
 **Datum:** Septembar 2025  

