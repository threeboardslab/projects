# DIY Smoke Detector v1

A working smoke detector for under $4 in components. Green LED when the
air is clean, red LED and buzzer alarm when it detects smoke or combustible
gas.

**Full build writeup with photos and video:**
👉 [threeboardslab.com/projects/smoke-detector-v1](https://threeboardslab.com/projects/smoke-detector-v1)

## Parts

| Part | Qty |
|---|---|
| Arduino Uno | 1 |
| MQ-2 Gas Sensor | 1 |
| Buzzer | 1 |
| LED (green) | 1 |
| LED (red) | 1 |
| 220Ω Resistor | 2 |
| Breadboard | 1 |
| Jumper wires | ~10 |

## Wiring

| From | To |
|---|---|
| MQ-2 VCC | Arduino 5V |
| MQ-2 GND | Arduino GND |
| MQ-2 AO | Arduino A0 |
| MQ-2 DO | Arduino D7 |
| Green LED + 220Ω | Arduino D9 → GND |
| Red LED + 220Ω | Arduino D10 → GND |
| Buzzer | Arduino D11 |

## How to use

1. Wire it up per the table above.
2. Open `smoke-detector-v1.ino` in Arduino IDE (or PlatformIO).
3. Select board: Arduino Uno. Pick the correct serial port.
4. Upload.
5. Open Serial Monitor at 9600 baud to see the live sensor readings.
6. Wait for the 20-second warm-up (green LED blinks).
7. Test by blowing smoke or holding a lighter near the sensor (briefly).

## Tuning

- `SMOKE_THRESHOLD` (default 400) — raise if you get false alarms, lower
  for a more sensitive detector. Range is 0–1023.
- `BUZZER_FREQ` (default 2000 Hz) — alarm tone frequency. Two-tone alarm
  alternates between this and `BUZZER_FREQ - 400`.
- `READ_INTERVAL` (default 500 ms) — how often to sample the sensor when
  air is clean.

## License

MIT — see [../LICENSE](../LICENSE). Build with it, ship products with it,
fork it. Attribution appreciated but not required.
