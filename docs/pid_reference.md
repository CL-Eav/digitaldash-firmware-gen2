# PID Reference Table

All PIDs defined in `lib/lib_pid/src/pid.h`.

**Modes:**
- `MODE1` — Standard OBD-II (SAE J1979)
- `MODE22` — Ford extended diagnostic PIDs
- `CALC1` — Calculated/derived value
- `SNIFF` — Passive CAN bus sniffer (no ECU query)

---

| # | Name | PID | Mode | CAN Header | Units | Min | Max |
|---|------|-----|------|------------|-------|-----|-----|
| 1 | Accel Pedal Position | 0x005A | MODE1 | 0x7E0 | PERCENT | 0 | 100 |
| 2 | Air-Fuel Ratio (O2 Sensor 1) | 0x0034 | MODE1 | 0x7E0 | RATIO | 0 | 29.4 |
| 3 | Ambient Air Temp | 0x057D | MODE22 | 0x7E0 | °C / °F | -40 / -40 | 200 / 400 |
| 4 | Barometric Pressure | 0x0033 | MODE1 | 0x7E0 | KPA / PSI / BAR | 0 | 255 / 36 / 2.55 |
| 5 | Battery Voltage | 0x0042 | MODE1 | 0x7E0 | VOLTS | 0 | 24 |
| 6 | Boost | 0x006F | MODE1 | 0x7E0 | KPA / PSI / BAR | 0 | 255 / 36 / 2.55 |
| 7 | Boost / Vacuum (calculated) | 0x006F | CALC1 | 0x7E0 | KPA / PSI / BAR | -82 / -12 / -0.82 | 170 / 24 / 1.7 |
| 8 | Brake Pedal Status | 0x0802 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 9 | Calculated Engine Load | 0x0004 | MODE1 | 0x7E0 | PERCENT | 0 | 100 |
| 10 | Catalytic Temperature | 0xF43C | MODE22 | 0x7E0 | °C / °F | 0 / 0 | 1000 / 2000 |
| 11 | Charge Air Temp [ST] | 0x0461 | MODE22 | 0x7E0 | °C / °F | -40 / -40 | 200 / 400 |
| 12 | Commanded Air-Fuel Ratio | 0x0044 | MODE1 | 0x7E0 | RATIO | 0 | 29.4 |
| 13 | Cruise Control CAN Button | 0x0306 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 14 | Cruise Control OFF Button | 0x0302 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 15 | Cruise Control OFF Button (toggle) | 0x0302 | CALC1 | 0x7E0 | NONE | 0 | 1 |
| 16 | Cruise Control ON Button | 0x0301 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 17 | Cruise Control RES Button | 0x0305 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 18 | Cruise Control SET- Button | 0x0304 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 19 | Cruise Control SET+ Button | 0x0303 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 20 | Emergency Brake Status | 0x0C82 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 21 | Engine Load | 0xF404 | MODE22 | 0x7E0 | PERCENT | 0 | 100 |
| 22 | Engine Coolant Temp | 0x0005 | MODE1 | 0x7E0 | °C / °F | -40 / -40 | 215 / 400 |
| 23 | Engine Speed | 0x000C | MODE1 | 0x7E0 | RPM | 0 | 8000 |
| 24 | Engine Speed (sniffer) | 0x000C | SNIFF | 0x7E0 | RPM | 0 | 8000 |
| 25 | Fuel Pressure | 0x000A | MODE1 | 0x7E0 | KPA / PSI / BAR | 0 | 765 / 110 / 7.65 |
| 26 | Fuel Rail Pressure | 0x0022 | MODE1 | 0x7E0 | KPA / PSI / BAR | 0 | 5177 / 750 / 51.77 |
| 27 | Gauge Illumination Level | 0x01C8 | SNIFF | 0x7E0 | NONE | 0 | 31 |
| 28 | Ignition Correction Cylinder 1 | 0x03EC | MODE22 | 0x7E0 | DEGREES | -16 | 16 |
| 29 | Intake Air Temp | 0x000F | MODE1 | 0x7E0 | °C / °F | -40 / -40 | 200 / 400 |
| 30 | Intake Air Temp (extended) | 0xF40F | MODE22 | 0x7E0 | °C / °F | -40 / -40 | 200 / 400 |
| 31 | LP Fuel Duty Cycle | 0x0307 | MODE22 | 0x7E0 | PERCENT | 0 | 100 |
| 32 | Lateral Acceleration | 0x1802 | SNIFF | 0x180 | G_FORCE | -2 | 2 |
| 33 | Long Term Fuel Trim Bank 1 | 0x0007 | MODE1 | 0x7E0 | PERCENT | -100 | 99.2 |
| 34 | Long Term Fuel Trim Bank 2 | 0x0009 | MODE1 | 0x7E0 | PERCENT | -100 | 99.2 |
| 35 | Longitudinal Acceleration | 0x1602 | SNIFF | 0x160 | G_FORCE | -2 | 2 |
| 36 | Manifold Absolute Pressure | 0x000B | MODE1 | 0x7E0 | KPA / PSI / BAR | 0 | 255 / 36 / 2.55 |
| 37 | MAP Sensor 1 Voltage | 0x0301 | MODE22 | 0x7E0 | VOLTS | 0 | 5 |
| 38 | Manifold Charge Temp [RS] | 0x03CA | MODE22 | 0x7E0 | °C / °F | -40 / -40 | 200 / 400 |
| 39 | Mass Air Flow | 0x0010 | MODE1 | 0x7E0 | g/s | 0 | 655.35 |
| 40 | O2 Sensor 2 Voltage | 0x0015 | MODE1 | 0x7E0 | VOLTS | 0 | 1.275 |
| 41 | Octane Adjust Ratio | 0x03E8 | MODE22 | 0x7E0 | RATIO | -1 | 1 |
| 42 | Oil Temperature | 0x005C | MODE1 | 0x7E0 | °C / °F | -40 / -40 | 200 / 400 |
| 43 | Reverse Status | 0x0803 | SNIFF | 0x7E0 | NONE | 0 | 1 |
| 44 | Short Term Fuel Trim Bank 1 | 0x0006 | MODE1 | 0x7E0 | PERCENT | -100 | 99.2 |
| 45 | Short Term Fuel Trim Bank 2 | 0x0008 | MODE1 | 0x7E0 | PERCENT | -100 | 99.2 |
| 46 | Throttle Position | 0x0011 | MODE1 | 0x7E0 | PERCENT | 0 | 100 |
| 47 | Timing Advance | 0x000E | MODE1 | 0x7E0 | DEGREES | -64 | 63.5 |
| 48 | VCT Exhaust Cam Solenoid Duty Cycle | 0x0317 | MODE22 | 0x7E0 | PERCENT | 0 | 100 |
| 49 | VCT Intake Cam Solenoid Duty Cycle | 0x0316 | MODE22 | 0x7E0 | PERCENT | 0 | 100 |
| 50 | Vehicle Speed | 0x000D | MODE1 | 0x7E0 | KMH / MPH | 0 | 270 / 180 |
| 51 | Vehicle Status | 0x1260 | SNIFF | 0x7E0 | NONE | 0 | 1 |
