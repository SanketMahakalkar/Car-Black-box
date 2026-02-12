# 🚘 Car Black Box (Event Data Recorder)

A real-time **Event Data Recorder (EDR)** designed to simulate a vehicle's "Black Box." This system captures critical driving events (Gear Shifts, Speed, Collisions) with precise timestamps and stores them in **External EEPROM** using the **I2C Protocol**, ensuring data is retained even after power failure.

> **Project Type:** Emertxe Embedded Systems Project
> **Status:** Completed

---

## 🚀 System Overview
Engineered a robust vehicle logging system using the **PIC16F877A** microcontroller. The system acts as a digital witness for accidents by continuously monitoring vehicle speed and gear status. When a critical event occurs (such as a collision or aggressive gear shift), the system logs the exact timestamp and speed into non-volatile memory for later analysis.

---

## 🔑 Key Features
* **Real-Time Event Logging:** Captures and stores:
    * **Gear Shifts** (Reverse, Neutral, Gear 1-4)
    * **Vehicle Speed** (0-99 km/h)
    * **Collision Events** (Instant recording via Interrupts)
* **Non-Volatile Storage (I2C):** Implemented **External EEPROM (AT24C04)** storage using the **I2C Protocol** to prevent data loss during power cuts.
* **Optimized Interrupts:** Utilized **ISRs (Interrupt Service Routines)** to handle high-priority events (like crashes) immediately without blocking the main loop.
* **Secure Dashboard:** Features a password-protected menu accessible via **Matrix Keypad** to view and download event logs on the **16x2 CLCD**.
* **Simulation Mode:** Uses **ADC (Potentiometer)** to simulate varying vehicle speeds and external switches to trigger collision scenarios.

---

## 🛠️ Tech Stack
* **Microcontroller:** PIC16F877A (8-bit RISC)
* **Language:** Embedded C
* **IDE:** MPLAB X IDE
* **Compiler:** XC8
* **Communication Protocols:**
    * **I2C:** For External EEPROM (AT24C04) and RTC (DS1307).
    * **UART:** For serial debugging (optional).
* **Peripherals:** ADC (Analog-to-Digital Converter), Timers, External Interrupts.

---

## 🔌 Hardware Architecture
| Component | Interface | Function |
| :--- | :--- | :--- |
| **PIC16F877A** | Main Controller | Processes inputs and manages protocol communication. |
| **External EEPROM** | I2C (RC3/RC4) | Stores the last 10 events permanently. |
| **RTC (DS1307)** | I2C (RC3/RC4) | Provides precise timestamps (HH:MM:SS) for logs. |
| **CLCD (16x2)** | 4-bit Parallel | Displays the dashboard, menu, and logs. |
| **Matrix Keypad** | GPIO (PORTB) | User interface for gear shifting and password entry. |
| **Potentiometer** | ADC (AN4) | Simulates the vehicle's speed sensor. |

---

## ⚙️ How It Works
1.  **Driving Mode (Default):**
    * The screen displays **Time (HH:MM:SS)**, **Event (GR/ON/C)**, and **Speed (XX)**.
    * Use the **Potentiometer** to change speed.
    * Use **Keypad (SW2/SW3) or (Rb1/Rb2)** to shift gears (UP/DOWN).
2.  **Collision Simulation:**
    * Press **Switch 1** (External Interrupt RB0) to simulate a crash.
    * The system instantly logs: `"C  [Speed] [Time]"` into EEPROM.
3.  **View Logs (Admin Mode):**
    * Press **Switch 4 or RB4** (Menu) to enter the log menu.
    * Enter the 4-digit Password (Default: `Rb4 Rb3 Rb4 Rb3`).
    * Scroll through the last 10 saved events using the keypad,Rb3 up , Rb4 down, Rb5 select.

---



## 👨‍💻 Author
**Sanket Mahakalkar**
* [LinkedIn](https://linkedin.com/in/sanket-mahakalkar)
* [GitHub](https://github.com/SanketMahakalkar)
