## 🚀 Dual Functional Embedded Gadget (Arduino)

This project implements a **multi-mode embedded system** on an Arduino-based development board using structured C/C++ programming. The system integrates two main functionalities: a **Spirit Level** using an accelerometer and a **Countdown Timer**, with a simple user interface and mode switching.

---

## 💡 Overview

The system operates across three modes:
- Title Page
- Spirit Level
- Timer  

A state machine is used to manage transitions between modes, ensuring a structured and user-friendly interaction.

---

## ⚙️ Features

### 📄 Title Page
- Displays system information on LCD  
- Waits for user input (S2 button) to proceed  
- Red LED indicates active state  

---

### 🧭 Spirit Level Mode
- Uses accelerometer data to detect tilt (X-axis)  
- Averages multiple readings for improved stability  
- Displays tilt direction and magnitude on LCD  
- Visual feedback using LED patterns:
  - Flat  
  - Slight / Medium / Extreme left tilt  
  - Slight / Medium / Extreme right tilt  
- Yellow LED indicates active state  

---

### ⏱️ Timer Mode
- User inputs time (0–999 seconds) via keypad  
- Countdown displayed on LCD  
- 7-segment display shows unit digit  
- LED bank shows tens value  
- Can be aborted using S1 button  
- Completion indicated with buzzer (3 beeps)  
- Green LED indicates active state  

---

## 🧠 Key Concepts Demonstrated

- Finite State Machine (FSM) design  
- Sensor data processing (accelerometer)  
- Averaging/filtering techniques  
- User input handling (buttons & keypad)  
- Multi-output display control (LCD, LEDs, 7-seg)  
- Embedded C/C++ programming  

---

## 🔧 Hardware Used

- Arduino-compatible development board  
- Accelerometer module  
- LCD display  
- 7-segment display  
- LED bank  
- Push buttons (S1, S2)  
- Buzzer  

---

## 🔁 System Flow

The system cycles through modes in the following order:
