// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

import React from 'react';
import TrajectoryMap from './components/TrajectoryMap';
import probeDataRaw from './data/J4840152.json';
import { TelemetryPacket } from './types/telemetry';
import './App.css'; // Estilos globais (se existirem)

// Cast seguro dos dados estáticos para a nossa interface rigorosa
const flightData: TelemetryPacket[] = probeDataRaw as TelemetryPacket[];

const App: React.FC = () => {
  return (
    <div style={{ display: 'flex', flexDirection: 'column', height: '100vh' }}>
      <header style={headerStyle}>
        <h1>Aerospace Telemetry Dashboard</h1>
        <span>Engineered by @fulviofavilla</span>
      </header>

      <main style={{ flex: 1 }}>
        <TrajectoryMap data={flightData} />
      </main>
    </div>
  );
};

const headerStyle: React.CSSProperties = {
  backgroundColor: '#1e1e1e',
  color: '#ffffff',
  padding: '1rem 2rem',
  display: 'flex',
  justifyContent: 'space-between',
  alignItems: 'center',
  fontFamily: 'monospace'
};

export default App;
