// Code 1

// Simple OPB704 Reflective Sensor Test
// Turns on LED (D13) when object detected (reflection)

const int sensorPin = 2;   // Phototransistor collector connected here
const int ledPin = 13;     // Built-in LED on Arduino Uno

void setup() {
  pinMode(sensorPin, INPUT_PULLUP);  // enable internal pull-up resistor
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("OPB704 Reflective Sensor Test Started");
}

void loop() {
  int sensorState = digitalRead(sensorPin); 
  // HIGH = no reflection, LOW = reflection detected

  if (sensorState == LOW) {
    // Object detected (reflection)
    digitalWrite(ledPin, HIGH);
    Serial.println("Object detected");
  } else {
    // No reflection
    digitalWrite(ledPin, LOW);
    Serial.println("No object");
  }

  delay(200); // small delay for readability
}