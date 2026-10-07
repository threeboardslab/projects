# DIY Smoke Detector v2

An ESP32 smoke and gas detector that shows a live smoke level (0–100%) on a
built-in TFT and sends a Telegram alert to your phone the moment the air
crosses the line. Red LED and buzzer on alarm, green LED when the air is
clear. Under $25 in parts.

**Full build writeup with photos and video:**
👉 [threeboardslab.com/projects/smoke-detector-v2](https://threeboardslab.com/projects/smoke-detector-v2)

## Parts

| Part | Qty |
|---|---|
| ESP32 DevKit with built-in ST7789 TFT (170x320) | 1 |
| MQ-2 Gas Sensor | 1 |
| Active buzzer | 1 |
| LED (red, 5mm) | 1 |
| LED (green, 5mm) | 1 |
| 220–330Ω Resistor | 2 |
| 1kΩ Resistor | 1 |
| 2kΩ Resistor | 1 |
| Jumper wires | ~10 |

## Wiring

| From | To |
|---|---|
| MQ-2 VCC | 5V |
| MQ-2 GND | GND |
| MQ-2 AO | 1kΩ → ESP32 GPIO34 (plus 2kΩ from GPIO34 → GND) |
| Red LED + 220–330Ω | ESP32 GPIO13 → GND |
| Green LED + 220–330Ω | ESP32 GPIO14 → GND |
| Buzzer (+) | ESP32 GPIO12, (−) → GND |
| TFT | Built-in, on the board's own SPI pins |

The MQ-2 output can swing above 3.3V, so the 1k/2k divider keeps GPIO34
inside the ESP32's safe range. All grounds are common. GPIO12 is a
strapping pin — if your board won't boot, move the buzzer to GPIO27.

## How to use

1. Wire it up per the table above.
2. Open `smoke-detector-v2.ino` in Arduino IDE.
3. Install the Arduino-ESP32 core (built on 3.3.10) and the libraries
   **Adafruit GFX** and **Adafruit ST7789**.
4. Fill in `WIFI_SSID`, `WIFI_PASS`, `BOT_TOKEN` and `CHAT_ID` at the top.
   - Bot token: create a bot with @BotFather in Telegram.
   - Chat ID: send your bot a message, then open
     `https://api.telegram.org/bot<TOKEN>/getUpdates`.
5. Select your ESP32 board and port, then upload.
6. Open Serial Monitor at 115200 baud.
7. Wait for the ~3-minute warm-up — alarms stay off while the MQ-2 heater
   settles.
8. Test by holding a smoking incense stick near the sensor (briefly).

WiFi is 2.4GHz only on the ESP32.

## Tuning

- `SMOKE_BASELINE` (default 700) — raw reading in clean air, shown as 0%.
- `SMOKE_THRESH` (default 1500) — raw reading shown as 100%, where the alarm
  fires. Raise it if you get false alarms, lower it for a more sensitive
  detector. Raw range is 0–4095.
- `ALARM_CONSECUTIVE` (default 3) — readings in a row above the threshold
  before the alarm fires.
- `CLEAR_PERCENT` (default 80) — the level has to drop back under this
  before the alarm clears.
- `WARMUP_MS` (default 180000) — warm-up time after power-on, in ms.
- `READ_INTERVAL` (default 500 ms) — how often the sensor is sampled.

## License

MIT — see [../LICENSE](../LICENSE). Build with it, ship products with it,
fork it. Attribution appreciated but not required.
