// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

import React from 'react';
import { MapContainer, TileLayer, Polyline, Marker, Popup } from 'react-leaflet';
import 'leaflet/dist/leaflet.css';
import L from 'leaflet';
import { TelemetryPacket } from '../types/telemetry';

// Fix for default Leaflet icon missing in Webpack builds
delete (L.Icon.Default.prototype as any)._getIconUrl;
L.Icon.Default.mergeOptions({
    iconRetinaUrl: require('leaflet/dist/images/marker-icon-2x.png'),
    iconUrl: require('leaflet/dist/images/marker-icon.png'),
    shadowUrl: require('leaflet/dist/images/marker-shadow.png'),
});

interface TrajectoryMapProps {
    data: TelemetryPacket[];
}

const TrajectoryMap: React.FC<TrajectoryMapProps> = ({ data }) => {
    if (!data || data.length === 0) return <div>Sem dados de telemetria disponíveis.</div>;

    // Extração rigorosa das coordenadas
    const positions: [number, number][] = data.map(packet => [packet.lat, packet.lon]);
    const lastPoint = positions[positions.length - 1];
    const lastTelemetry = data[data.length - 1];

    return (
        <MapContainer center={lastPoint} zoom={10} style={{ height: "100%", width: "100%" }}>
            <TileLayer
                attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
                url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
            />
            <Polyline positions={positions} color="#00d2ff" weight={4} opacity={0.8} />

            <Marker position={lastPoint}>
                <Popup>
                    <strong>Sonda:</strong> {lastTelemetry.serial} <br />
                    <strong>Altitude:</strong> {lastTelemetry.alt.toFixed(2)} m <br />
                    <strong>Velocidade (V):</strong> {lastTelemetry.vel_v.toFixed(2)} m/s <br />
                    <strong>Bateria:</strong> {lastTelemetry.batt} V
                </Popup>
            </Marker>
        </MapContainer>
    );
};

export default TrajectoryMap;
