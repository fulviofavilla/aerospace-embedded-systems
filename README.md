# Aerospace Trajectory Suite

![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)
![C++](https://img.shields.io/badge/C++-17-00599C.svg?logo=c%2B%2B)
![React](https://img.shields.io/badge/React-18.2-61DAFB.svg?logo=react)
![TypeScript](https://img.shields.io/badge/TypeScript-Strict-3178C6.svg?logo=typescript)

An end-to-end telemetry data pipeline and visualization suite designed for high-performance aerospace applications. This monorepo demonstrates a complete data engineering lifecycle: from low-level Unix Domain Socket data ingestion to real-time interactive mapping.

---

## Architecture

The suite is divided into two decoupled micro-architectures:

### 1. Core Engine (Backend / Data Ingestion)
A high-performance Unix Domain Socket (UDS) server written in **Modern C++17**.
* **Inter-Process Communication (IPC):** Listens for incoming telemetry streams via `AF_UNIX` sockets, ensuring minimal latency.
* **Persistent Black Box Logging:** Synchronously writes raw binary data streams (`.bin`) to disk using thread-safe RAII implementations, preventing data loss during flight operations.
* **Zero-Overhead:** Designed to run efficiently on embedded systems or lightweight environments.

### 2. Trajectory Browser (Frontend / Data Visualization)
A strict-typed **React & TypeScript** dashboard for mission control operators.
* **Strict Telemetry Interfaces:** Uses defined TypeScript interfaces to ensure data integrity when parsing flight data.
* **Geospatial Rendering:** Integrates `React-Leaflet` to plot dynamic flight paths, rendering altitude, velocity, and battery metrics on an interactive map.
* **Real-World Data:** The sample telemetry datasets included in `src/data` are sourced from **SondeHub**, representing actual radiosonde flight trajectories.

---

## Getting Started

### Prerequisites
* **C++ Engine:** `g++` (supports C++17) and `make`. Linux/WSL environment required for Unix Sockets.
* **Frontend:** `Node.js` (v16+) and `npm`.

### Running the Core Engine
Navigate to the C++ engine directory, build the binaries, and start the listener:
```bash
cd core-engine
make clean && make
./bin/telemetry_engine
```

To test the ingestion pipeline, open a new terminal and run `./bin/test_client`.

### Running the Trajectory Browser

Navigate to the frontend directory, install dependencies, and start the development server:

```bash
cd trajectory-browser
npm install
npm start
```

The dashboard will automatically open at http://localhost:3000.
