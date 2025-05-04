#include <DHT.h>

#define DHTPIN D4          // DHT sensor pin
#define DHTTYPE DHT22     // Sensor type
#define SPEAKER_PIN D1    // Speaker pin (no resistor needed)
#define ALERT_THRESHOLD 0.5  // Trigger alert when temp rises ≥0.5°C

DHT dht(DHTPIN, DHTTYPE);
float baselineTemp = 0;
bool alertTriggered = false;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Set initial baseline (average of 3 readings)
  setBaseline();
  
  Serial.print("Baseline temperature set to: ");
  Serial.print(baselineTemp, 1);
  Serial.println("°C");
}

void loop() {
  delay(2000); // Wait between readings
  
  float currentTemp = dht.readTemperature();
  if (isnan(currentTemp)) return;

  // Check temperature increase
  if (currentTemp > baselineTemp + ALERT_THRESHOLD && !alertTriggered) {
    triggerAlert(currentTemp);
    alertTriggered = true;
  } 
  else if (currentTemp <= baselineTemp) {
    alertTriggered = false; // Reset alert if temp drops back
  }

  Serial.print("Current: ");
  Serial.print(currentTemp, 1);
  Serial.print("°C | Change: ");
  Serial.print(currentTemp - baselineTemp, 1);
  Serial.println("°C");
}

void setBaseline() {
  float sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += dht.readTemperature();
    delay(1000);
  }
  baselineTemp = sum / 3;
}

void triggerAlert(float temp) {
  Serial.println("ALERT: Temperature rising!");
  
  // 1. Warning tone sequence (3 rising notes)
  tone(SPEAKER_PIN, 262, 200); delay(300); // C4
  tone(SPEAKER_PIN, 330, 200); delay(300); // E4
  tone(SPEAKER_PIN, 392, 300); delay(400); // G4
  
  // 2. Speak current temperature
  speakNumber(temp);
  
  // 3. "Degrees" tone
  tone(SPEAKER_PIN, 523, 400); delay(500); // C5
  noTone(SPEAKER_PIN);
}

void speakNumber(float num) {
  int whole = (int)num;
  int decimal = (int)((num - whole) * 10);
  
  // Whole number beeps
  for (int i = 0; i < whole; i++) {
    tone(SPEAKER_PIN, 440, 200); // A4
    delay(300);
  }
  
  // Decimal point (high ping)
  tone(SPEAKER_PIN, 880, 100); // A5
  delay(150);
  
  // Decimal beeps
  for (int i = 0; i < decimal; i++) {
    tone(SPEAKER_PIN, 440, 100);
    delay(150);
  }
}
