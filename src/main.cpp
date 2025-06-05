#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

// ESP32 Brownout fix
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

MAX30105 sensor;

long lastBeat = 0;
float beatsPerMinute;
float beatAvg = 0;

bool fingerDetected = false;
const int IR_THRESHOLD = 50000;

// GPIO Pins
const int greenLED = 2;   // D2 → Finger detected
const int redLED = 4;     // D4 → No finger
const int buzzer = 5;     // Buzzer

// PWM for buzzer
const int buzzerChannel = 0;
const int buzzerFreq = 1000;           // Lower pitch tone
const int buzzerResolution = 8;        // 8-bit PWM (0–255)
const int buzzerVolume = 5;           // Lower volume (0–255)

void setup() {
  // Disable brownout detector on ESP32
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  Serial.begin(115200);
  delay(1000);  // Wait for Serial Monitor

  // Set pin modes
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Setup buzzer PWM
  ledcSetup(buzzerChannel, buzzerFreq, buzzerResolution);
  ledcAttachPin(buzzer, buzzerChannel);

  // Initialize MAX30102
  if (!sensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("❌ MAX30102 not found. Check wiring.");
    digitalWrite(redLED, HIGH);
    ledcWriteTone(buzzerChannel, buzzerFreq);
    ledcWrite(buzzerChannel, buzzerVolume);  // Quieter buzzer
    while (1);
  }

  Serial.println("✅ MAX30102 ready. Place your finger on the sensor.");

  sensor.setup(); // Load default settings
  sensor.setPulseAmplitudeRed(0x3F);    // Medium red LED
  sensor.setPulseAmplitudeGreen(0);     // Turn off internal green LED
}

void loop() {
  long irValue = sensor.getIR();

  if (irValue > IR_THRESHOLD) {
    if (!fingerDetected) {
      fingerDetected = true;
      Serial.println("👉 Finger detected, measuring BPM...");

      // Green on, Red & Buzzer off
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      ledcWriteTone(buzzerChannel, 0);  // Stop buzzer
    }

    if (checkForBeat(irValue)) {
      long now = millis();
      long delta = now - lastBeat;
      lastBeat = now;

      if (delta > 300) {
        beatsPerMinute = 60 / (delta / 1000.0);
        if (beatsPerMinute >= 40 && beatsPerMinute <= 180) {
          beatAvg = (beatAvg == 0) ? beatsPerMinute : (beatAvg * 0.9 + beatsPerMinute * 0.1);

          Serial.print("❤️ Heart rate: ");
          Serial.print(beatsPerMinute, 1);
          Serial.print(" BPM | Avg: ");
          Serial.println(beatAvg, 1);
        }
      }
    }
  } else {
    if (fingerDetected) {
      Serial.println("👉 Place your finger on the sensor...");
      fingerDetected = false;
      lastBeat = 0;
      beatsPerMinute = 0;
      beatAvg = 0;

      // Green off, Red & Buzzer on
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      ledcWriteTone(buzzerChannel, buzzerFreq);         // Set tone
      ledcWrite(buzzerChannel, buzzerVolume);           // Lower volume
    }
  }

  delay(20); // Sampling delay
}
