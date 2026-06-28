/ Code 2:

// Anemometer rotation counter using reflective IR sensor
// Arduino Uno version (ATmega328P)

// Pin definitions
const uint8_t sensorPin = 2; // digital input pin 
volatile unsigned long pulseCount = 0; // counts the number of pulses (rotations)
unsigned long lastPrintTime = 0; // last time we printed stats
const unsigned long printInterval = 5000; // interval (ms) between stats prints

// Simple debounce: ignore pulses that occur too close together (in microseconds)
volatile unsigned long lastPulseMicros = 0;
const unsigned long minPulseIntervalMicros = 2000; // 2000 µs = 2 ms (adjust if needed)

void handlePulse() {
// very short ISR: check debounce and increment
unsigned long now = micros();
if ((now - lastPulseMicros) >= minPulseIntervalMicros) {
pulseCount++;
lastPulseMicros = now;
}
}
void setup() {
Serial.begin(9600);

// On Uno, waiting for serial isn't necessary; don't block with while(!Serial)
Serial.println(F("Anemometer rotation counter (IR sensor)"));
pinMode(sensorPin, INPUT_PULLUP);

// Attach interrupt on falling edge (when the reflective mark passes)
// For UNO: digitalPinToInterrupt(2) -> 0 (INT0)
attachInterrupt(digitalPinToInterrupt(sensorPin), handlePulse, FALLING);
lastPrintTime = millis();
}

void loop() {
unsigned long now = millis();
if (now - lastPrintTime >= printInterval) {

// Disable interrupts briefly to get stable count
noInterrupts();
unsigned long count = pulseCount;

// reset the count for the next interval
pulseCount = 0;
interrupts();

// Calculate rotations per minute (RPM) or other metric
// Suppose one pulse = one revolution
float revolutions = (float)count; // since one pulse per rev (adjust if different)
float revPerSec = revolutions / (printInterval / 1000.0);
float rpm = revPerSec * 60.0;
float speed = (2 * 3.1416 * 0.35) * (revPerSec);

Serial.print(F("Pulses in last "));
Serial.print(printInterval / 1000.0);
Serial.print(F(" s: "));
Serial.print(count);
Serial.print(F(" RPM: "));
Serial.println(rpm, 2);
Serial.print(F(" Wind speed: "));
Serial.println(speed);
lastPrintTime = now;
}

// small idle delay so loop isn't totally busy
delay(10);
}