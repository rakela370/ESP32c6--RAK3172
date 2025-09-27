# ESP32-C6 ↔ RAK3172 UART Komunikacija

Ovaj projekat demonstrira osnovnu **UART komunikaciju** između **ESP32-C6** i **RAK3172** LoRa modula korišćenjem ESP-IDF okruženja.  
Cilj je da se uspostavi dvosmerna komunikacija i proveri da li RAK3172 ispravno odgovara na osnovne **AT komande**.

---

##  Hardverske konekcije

| ESP32-C6 Pin | RAK3172 Pin | Opis |
|-------------|-------------|------|
| **4**       | **RX**      | TX ESP → RX RAK |
| **5**       | **TX**      | RX ESP ← TX RAK |
| **GND**     | **GND**     | Zajednička masa |
| **3V3**     | **VCC**     | Napajanje modula (3.3V) – **nikako 5V** |

---

##  Instalacija i pokretanje

1. Instalirati **ESP-IDF** 
2. Kreirati novi ESP-IDF projekat i kopirati `main.c` iz ovog repozitorijuma.
3. Postavite target:
   ```bash
   idf.py set-target esp32c6
   ```
4. Build i Flash:
   ```bash
   idf.py build
   ```
   ```bash
   idf.py -p /dev/ttyACM0 flash monitor
   ```

Ako je sve ispravno povezano, u serijskom monitoru ćete videti logove i odgovor RAK modula na `AT` komandu.

---

##  Objašnjenje koda

- **UART konfiguracija:**  
  Kod podešava UART1 port sa brzinom 115200, pinovima TX=4 i RX=5.  
- **Slanje podataka:**  
  Odmah nakon pokretanja šalje se `"AT\r\n"` komanda ka RAK modulu.
- **Čitanje podataka:**  
  U beskonačnoj petlji čita se sve što stigne sa RAK modula i ispisuje na serijski monitor.

---



##  Buduće proširenje

- Na osnovu ovog primera lako se može dodati **Ping/Pong logika**:  
  - Jedan uređaj šalje `"PING"` poruku, drugi odgovara `"PONG"`.
  - Dodati timer ili interrupt za periodično slanje paketa.
- Moguće proširenje za **LoRa mrežnu komunikaciju** i testiranje dometa između dve RAK3172 pločice.

---

 **Autori:** Nikola Rakic i Milos Markovic
 **Datum:** Septembar 2025  


