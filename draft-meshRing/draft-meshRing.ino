// MESH/RING CIRCUIT
// Created By: Lance and Joey Boy
// Subject: PSA - Instrumentation
// Date: December 10, 2024

// Pin definitions for fault inputs (using pull-up resistors)
const int fault1Pin = 4;
const int fault2Pin = 5;
const int fault3Pin = 6;
const int fault4Pin = 7;

// Pin definitions for outputs
const int outputA = 8;
const int outputB = 9;
const int outputC = 10;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  
  // Configure input pins with internal pull-up resistors
  pinMode(fault1Pin, INPUT_PULLUP);
  pinMode(fault2Pin, INPUT_PULLUP);
  pinMode(fault3Pin, INPUT_PULLUP);
  pinMode(fault4Pin, INPUT_PULLUP);
  
  // Configure output pins
  pinMode(outputA, OUTPUT);
  pinMode(outputB, OUTPUT);
  pinMode(outputC, OUTPUT);
}

void loop() {
  // Read fault states
  bool fault1 = digitalRead(fault1Pin) == LOW;
  bool fault2 = digitalRead(fault2Pin) == LOW;
  bool fault3 = digitalRead(fault3Pin) == LOW;
  bool fault4 = digitalRead(fault4Pin) == LOW;

  // Default state: all outputs ON
  bool stateA = true;
  bool stateB = true;
  bool stateC = true;

  // Check combinations first
  if (fault1 && fault2) {
    stateA = false;
    Serial.println("Fault combination 1 and 2 detected! Output A is OFF");
  }
  else if (fault2 && fault4) {
    stateB = false;
    Serial.println("Fault combination 2 and 4 detected! Output B is OFF");
  }
  else if (fault3 && fault4) {
    stateC = false;
    Serial.println("Fault combination 3 and 4 detected! Output C is OFF");
  }
  else if (fault2 && fault3) {
    stateB = false;
    stateC = false;
    Serial.println("Fault combination 2 and 3 detected! Outputs B and C are OFF");
  }
  else if (fault1 && fault4) {
    stateA = false;
    stateB = false;
    Serial.println("Fault combination 1 and 4 detected! Outputs A and B are OFF");
  }
  else if (fault1 && fault3) {
    stateA = false;
    stateB = false;
    stateC = false;
    Serial.println("Fault combination 1 and 3 detected! All outputs are OFF");
  }
  // Single faults
  else {
    if (fault1) Serial.println("Single Fault 1 detected! All outputs remain ON");
    if (fault2) Serial.println("Single Fault 2 detected! All outputs remain ON");
    if (fault3) Serial.println("Single Fault 3 detected! All outputs remain ON");
    if (fault4) Serial.println("Single Fault 4 detected! All outputs remain ON");
  }

  // Apply the output states
  digitalWrite(outputA, stateA ? HIGH : LOW);
  digitalWrite(outputB, stateB ? HIGH : LOW);
  digitalWrite(outputC, stateC ? HIGH : LOW);

  delay(100);
}
