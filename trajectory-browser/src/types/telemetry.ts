// SPDX-License-Identifier: MIT
// Copyright (c) 2022 Fulvio Favilla (@fulviofavilla)

export interface TelemetryPacket {
    alt: number;
    batt: number;
    burst_timer: number;
    datetime: string;
    frame: number;
    frequency: number;
    heading: number;
    lat: number;
    lon: number;
    manufacturer: string;
    position: string;
    sats: number;
    serial: string;
    snr: number;
    type: string;
    upload_time_delta: number;
    uploader_alt: number;
    uploader_antenna: string;
    uploader_callsign: string;
    uploader_position: string;
    vel_h: number;
    vel_v: number;
}
