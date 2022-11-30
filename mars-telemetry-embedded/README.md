# Mars Telemetry & Embedded Controller

This module handles the end-to-end flow of Martian environmental data, from cloud ingestion to hardware-level thermal representation. Developed originally for the **OBSAT (Brazilian Satellite Olympiad)** framework.

## Module Structure

* `telemetry/`: Python scripts for interfacing with NASA's Mars Weather RSS/API.
* `hardware_simulation/`: MicroPython firmware for ESP32 and circuit definitions.
* `tutorial/`: Educational materials for aerospace data modeling.

## Technical Overview

### 1. Data Ingestion (`/telemetry`)
A robust Python pipeline that fetches Sol-based telemetry. It filters raw NASA JSON data into a lightweight payload optimized for embedded devices with limited memory.

### 2. Thermal Controller (`/hardware_simulation`)
The ESP32 firmware utilizes **Pulse Width Modulation (PWM)** to map Martian temperatures to an RGB scale.
* **Logic:** Converts Celsius to Kelvin to maintain a positive-only scale for duty cycle mapping.
* **Frequency:** 500Hz for stable LED visual output.

### 3. Data Modeling & Analysis (`/tutorial`)
The core analytical component of the module. It utilizes **NumPy** and **Matplotlib** to bridge the gap between raw telemetry and hardware states.
* **Thermal Modeling:** Implements a sinusoidal interpolation to estimate diurnal temperature variations based on daily Min/Max peaks.
* **Data Validation:** Includes pre-processing checks to handle missing "Sol" entries from the NASA RSS feed.

## Hardware Configuration

To replicate the thermal simulation, connect an **RGB LED (Common Anode/Cathode)** to the following ESP32 GPIOs:

| Component | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **Red Channel** | GPIO 14 | PWM Thermal Intensity (Warm) |
| **Green Channel** | GPIO 13 | PWM Thermal Intensity (Balanced) |
| **Blue Channel** | GPIO 12 | PWM Thermal Intensity (Cold) |
| **Common** | VIN / GND | Power Supply |

## Data Contract (JSON Schema)

The ingestion pipeline (`telemetry/`) produces a normalized payload to ensure compatibility with embedded memory constraints:

```json
[
  {
    "date": "YYYY-MM-DD",
    "min_temp": "float",
    "max_temp": "float"
  }
]
```

## How to Run

### Ingestion Pipeline
```bash
python telemetry/mars_telemetry_ingestion.py
```

### Embedded Simulation

1. Flash esp32_thermal_controller.py to an ESP32 using Thonny or ampy.

2. Ensure the mars_weather_mock.json is present in the filesystem for offline simulation.
