# Embedded-Programming
## 🚀 Embedded Systems Project: Real-Time Concurrent Processing

This project showcases the design and implementation of a real-time embedded system built on the ATmega328P microcontroller, focusing on concurrent task execution, low-level hardware control, and efficient system architecture.

Developed as part of my Embedded Systems coursework, this project goes beyond standard Arduino programming by using a fully bare-metal approach, directly interfacing with hardware registers to maximize performance, control, and efficiency.

---

## 💡 Key Highlights

### ⚡ Bare-Metal Programming
- Engineered without Arduino abstraction layers (`digitalWrite`, `pinMode`, etc.)
- Demonstrates strong understanding of low-level microcontroller architecture and register manipulation

### 🔄 Custom Task Scheduler
- Designed and implemented a non-blocking cooperative scheduler
- Enables multiple independent modules to run concurrently in real time

### 🧠 Scalable Embedded Architecture
- Modular design allowing seamless interaction between subsystems
- Includes traffic control, ADC monitoring, and user input handling

### ⏱️ Deterministic Timing & Responsiveness
- Precise timing using non-blocking logic
- Reliable system behavior under concurrent workloads

---

## 🛠️ System Features

### 🚦 Intelligent Traffic Light Controller
- Simulates a real-world 2-way intersection system
- Supports dynamic priority modes (North-South / East-West / Equal)
- Uses state machine logic with adaptive timing

### 🔋 Real-Time Voltage Monitoring (ADC)
- Samples analog input every 40ms
- Maps voltage ranges to LED indicators
- Demonstrates ADC integration

### 🔢 Event-Driven Counter System
- Button-controlled with debounce handling
- Displays hexadecimal values on a 7-segment display
- Maintains state across modes

### 🔘 Robust Input Handling
- Two push-buttons with non-blocking debounce (300ms)
- Reliable user input detection

### ❤️ System Heartbeat Monitor
- Visual indicator using 7-segment display
- Confirms real-time execution

### 🔁 Multi-Mode Operation
- 5 operational modes
- Dynamic module activation and system reconfiguration

---

## 🧠 Core Engineering Concepts

- Embedded C/C++
- Direct register manipulation
- Cooperative multitasking
- Finite State Machines (FSM)
- Real-time system design
- ADC interfacing
- Shift register communication (bit-banging)

---

## 🔧 Hardware Platform

- ATmega328P microcontroller (Arduino Uno compatible)
- Breadboard circuit
- LEDs (traffic + voltage indicators)
- 7-segment display (shift register)
- Push buttons

---

## 📈 Impact & Learning Outcomes

- Built real-time embedded systems from scratch  
- Designed scalable firmware architectures  
- Strengthened hardware-software integration skills  
- Optimized performance using bare-metal programming  
