# Autonomous Micromouse Maze-Solver (STM32 IDE & C) — 🏆 1st Place Winner

## 📌 Project Overview
This repository contains the system architecture and control logic firmware for an autonomous maze-running robot powered by an STM32 microcontroller. The robot successfully mapped, localized, and solved an unknown maze layout in under 4 minutes, earning **1st Place** among all competitive university groups for achieving the fastest time and the most stable runtime trajectory.

> 🔒 *Note: To maintain academic integrity and prevent plagiarism for ongoing university cohorts, the full raw production source code is withheld. A conceptual architecture overview and logic breakdowns are detailed below.*

---

## 🛠️ System Architecture & Tech Stack

### Hardware Integration
* **Microcontroller Unit:** STM32 (ARM Cortex-M core)
* **Sensors:** Interfaced a custom sensor fusion array combining Ultrasonic sensors (for long-range distance tracking) and Infrared (IR) sensors (for high-accuracy wall-detection and precise alignment mapping).
* **Actuation:** Dual closed-loop DC motors equipped with high-resolution magnetic quadrature encoders.

### Software & Environment
* **Language:** C / Bare-Metal Hardware Interfacing
* **IDE & Tools:** STM32CubeIDE, ST-LINK Debugger, PLCSIM/Logic Analyzers

---

## ⚙️ Core Engineering Implementation

### 1. Dual-Loop PID Control Algorithm
To manage rapid 90-degree cornering and stable straight-line acceleration without drifting into walls, the firmware utilizes an independent dual-loop PID control layout. 

* **Outer Loop (Distance Correction):** Processes real-time analog/digital feedback from the side IR sensors to calculate systemic cross-track error (axial drift from the center of the path).
* **Inner Loop (Velocity Matching):** Translates the cross-track error into differential PWM adjustments across the left and right motor drivers, matching encoder tick rates instantly to maintain stability.

### 2. Sensor Fusion & Wall-Detection Logic
The sensor array is evaluated concurrently using hardware timer interrupts to eliminate processing lag:
* **Ultrasonic Routine:** Triggers at fixed intervals to scan for upcoming forward obstructions.
* **IR Calibration Routine:** Dynamically normalizes ambient light readings via baseline software offsets, preventing false-positive wall detections under varying room illumination.

---

## 📊 Key Results & Engineering Achievements
* **🏆 1st Place Position:** Outperformed all competitive peer groups in runtime stability and path optimization.
* **⏱️ Under 4-Minute Run:** Navigated and completely solved an unmapped, multi-turn maze environment within a tight 4-minute operational ceiling.
* **📈 Stability Metrics:** Zero physical wall collisions recorded during the final run due to the high-frequency execution of the PID correction loop.

---

## 📂 Project Directory Structure Layout
For visualization, the firmware architecture is organized as follows:
```text
├── Drivers/             # STM32 HAL / CMSIS core hardware abstractions
├── Core/
│   ├── Inc/             # Firmware Header Files Architecture
│   │   ├── pid_controller.h       # Dual-loop PID constants and control variables
│   │   ├── sensor_fusion.h        # ADC configuration & IR/Ultrasonic raw scaling 
│   │   ├── collision_prevention.h # Safety threshold limits & emergency stop protocols
│   │   ├── mapping_solver.h       # Maze coordinate mapping matrices & Flood-fill logic
│   │   └── drive_actuators.h      # PWM configuration & Quadrature Encoder readings
│   └── Src/             # Firmware Low-Level Implementation
│       ├── main.c                 # Primary state-machine sequencer & system initialization
│       ├── pid_controller.c       # Math processing for cross-track error alignment
│       ├── sensor_fusion.c        # Hardware interrupt timers handling raw analog streams
│       ├── collision_prevention.c # Real-time safe override routines avoiding walls
│       ├── mapping_solver.c       # Coordinate array memory management for maze tracking
│       └── drive_actuators.c      # Differential speed PWM mapping to encoder ticks
└── Documentation/       # Structural schematics and hardware block diagrams




## 📉 System Control Loop Flowchart
The control architecture manages spatial stabilization and differential velocity adjustments through the following runtime execution matrix:
```mermaid
flowchart TD
    %% Define System Input
    Start([Wall Distance Target]) --> PID_Calc[Outer Control Loop: Spatial Processing]
    
    %% Sensor Data Inputs
    Sensors[(IR & Ultrasonic Array)] -- Raw Telemetry Stream --> Fusion[Sensor Fusion & Calibration]
    Fusion -- Clean Linear Feedback --> DriftCalc[Calculate Cross-Track Error / Axial Drift]
    DriftCalc --> PID_Calc
    
    %% PID Mathematics Block
    PID_Calc --> Math{Execute PID Loop Math}
    Math -- Proportional Error --> Adjust[Compute Combined Alignment Adjustment]
    Math -- Integral Window --> Adjust
    Math -- Derivative Delta --> Adjust
    
    %% Emergency Guard Rail
    Adjust --> SafetyCheck{Collision Prevention Triggered?}
    SafetyCheck -- Over-threshold Proximity --> Emergency[Override: Immediate Stop/Pivot]
    SafetyCheck -- Safe Path Maintained --> Actuator[Inner Control Loop: Velocity Mapping]
    
    %% Actuation Out
    Actuator --> Encoder[Read Quadrature Encoders Tick Delta]
    Encoder --> MotorPWM[Update Left/Right Motor PWM Signals]
    MotorPWM --> Moving[Execute Physical Trajectory Correction]
    
    %% Feedback Loop
    Moving --> Sensors
