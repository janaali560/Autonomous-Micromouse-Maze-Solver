# Autonomous Micromouse Maze-Solver (STM32 IDE & C) — 🏆 1st Place Winner

## 📌 Project Overview
Developed the low-level firmware for an autonomous maze-running robot powered by an STM32 microcontroller. The system successfully mapped, localized, and solved an unknown maze layout in under 4 minutes, earning 1st Place out of all competitive groups for speed and trajectory stability.

## 🛠️ Technical Tech Stack
* **Microcontroller:** STM32 (ARM Cortex-M)
* **Languages & IDE:** C, STM32CubeIDE
* **Sensors:** Ultrasonic sensor arrays and Infrared (IR) sensors for spatial mapping and real-time wall detection.
* **Actuators:** Closed-loop DC motors.

## ⚙️ Core Logic & Algorithms
* **Dual-Loop PID Control:** Engineered a custom dual-loop PID control algorithm to independently govern the left and right motors, ensuring precise trajectory alignment, error-correction, and sharp 90-degree cornering.
* **Real-Time Data Integration:** Calibrated and synchronized the IR/Ultrasonic sensor fusion array to handle real-time mapping and localized spatial updates while on the move.
