/*
 * threeboardslab — DIY Smoke Detector v1
 * https://threeboardslab.com/projects/smoke-detector-v1
 *
 * Arduino smoke detector using an MQ-2 gas sensor, a buzzer, and two
 * status LEDs. Green when air is clean, red + buzzer when smoke or
 * combustible gas is detected.
 *
 * Hardware:
 *   Arduino Uno + MQ-2 sensor + buzzer + green LED + red LED +
 *   2x 220Ω resistors + breadboard + jumper wires
 *
 * Wiring:
 *   MQ-2 VCC -> Arduino 5V
 *   MQ-2 GND -> Arduino GND
 *   MQ-2 AO  -> Arduino A0
 *   MQ-2 DO  -> Arduino D7
 *   Green LED + 220Ω -> Arduino D9  -> GND
 *   Red LED   + 220Ω -> Arduino D10 -> GND
 *   Buzzer           -> Arduino D11
 *
 * License: MIT
 */

const int MQ2_AO     = A0;
const int MQ2_DO     = 7;
const int LED_GREEN  = 9;
const int LED_RED    = 10;
const int BUZZER     = 11;


const int SMOKE_THRESHOLD = 400;
const int BUZZER_FREQ     = 2000;
const int READ_INTERVAL   = 500;


bool alarmActive = false;


void setup() {
  Serial.begin(9600);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED,   OUTPUT);
  pinMode(BUZZER,    OUTPUT);
  pinMode(MQ2_DO,    INPUT);

  Serial.println("=============================");
  Serial.println("  threeboardslab Smoke Detector v1");
  Serial.println("  Warming up MQ-2 sensor...");
  Serial.println("=============================");

  for (int i = 20; i > 0; i--) {
    digitalWrite(LED_GREEN, HIGH);
    delay(500);
    digitalWrite(LED_GREEN, LOW);
    delay(500);
    Serial.print("Warm-up: ");
    Serial.print(i);
    Serial.println("s remaining...");
  }

  Serial.println("Ready! Monitoring...\n");
  digitalWrite(LED_GREEN, HIGH);
}


void loop() {
  int smokeLevel = analogRead(MQ2_AO);
  int doState    = digitalRead(MQ2_DO);


  Serial.print("Smoke Level: ");
  Serial.print(smokeLevel);
  Serial.print(" / 1023  |  Digital: ");
  Serial.print(doState == LOW ? "TRIGGERED" : "clear");
  Serial.print("  |  Status: ");

  if (smokeLevel > SMOKE_THRESHOLD || doState == LOW) {

    Serial.println("*** SMOKE DETECTED! ***");

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED,   HIGH);


    tone(BUZZER, BUZZER_FREQ);
    delay(200);
    noTone(BUZZER);
    delay(100);
    tone(BUZZER, BUZZER_FREQ - 400);
    delay(200);
    noTone(BUZZER);
    delay(100);

    alarmActive = true;

  } else {

    Serial.println("OK");

    if (alarmActive) {
      noTone(BUZZER);
      digitalWrite(LED_RED, LOW);
      alarmActive = false;
    }

    digitalWrite(LED_GREEN, HIGH);
    delay(READ_INTERVAL);
  }
}
