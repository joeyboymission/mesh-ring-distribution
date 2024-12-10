# Draft Project Planning
## Radial Circuit
**Description**: A radial circuit is a type of electrical wiring where each outlet or device is connected directly to the main power source. This configuration is simple and commonly used in residential installations.

### How it works:
In a radial circuit, power flows from the main distribution board to each outlet or device in a single path. Each outlet is connected in parallel, ensuring that if one outlet fails, the others remain operational.

### Uses
- Residential electrical installations
- Small office setups
- Simple lighting circuits

### Advantages
- Easy to install and maintain
- Cost-effective for small installations
- Faults are easier to locate and isolate

---

## Mesh/Ring Circuit
**Description**: A mesh/ring circuit is a network topology where each node is connected to two other nodes, forming a ring. This setup provides redundancy and ensures that the network remains operational even if one connection fails.

### How it works:
In a mesh/ring circuit, each node is connected to two other nodes, creating a circular data path. Data can travel in both directions, providing multiple pathways for communication. If one connection fails, data can still be transmitted through the alternate path.

### Uses
- Computer networks
- Telecommunications
- Industrial control systems

### Advantages
- High redundancy and reliability
- Efficient data transmission
- Scalable and flexible network design
- Fault tolerance ensures continuous operation


# Fault-Tolerant Electrical Network Monitoring: A Microcontroller-Driven Approach
## Concept
This part is stating about the brainstorming and concept thinking for the approach of and making of the system.

```python
def check_outputs(faults):
    outputs = ['A', 'B', 'C']
    
    if set([1, 2]) & set(faults):
        outputs[0] = 'OFF'
    if set([2, 4]) & set(faults):
        outputs[1] = 'OFF'
    if set([3, 4]) & set(faults):
        outputs[2] = 'OFF'
    
    return outputs

# Testing
faults = {1, 2}  # Set the fault for samples
result = check_outputs(faults)
print(result)
```

**Interpretation**: The following configuration is based on the Mesh/Ring Circuit condition that when:
- if no fault is triggered or off/open connection then all outputs 'A', 'B' and 'C' stays ON.
- if fault '1' is off/open connection then all outputs 'A'm 'B' and 'C' stays ON
- if fault '2' is off/open connection then all outputs 'A'm 'B' and 'C' stays ON
- if fault '3' is off/open connection then all outputs 'A'm 'B' and 'C' stays ON
- if fault '4' is off/open connection then all outputs 'A'm 'B' and 'C' stays ON 
- if fault '1' and '2' is off/open connection the output 'A' will be OFF while 'B' and 'C' is ON
- if fault '2' and '4' is off/open connection the output 'B' will be OFF while 'A' and 'C' is ON
- if fault '3' and '4' is off/open connection the output 'C' will be OFF while 'A' and 'B' is on
- if fault '2' and '3' is off/open connection  then all outputs 'A', 'B' and 'C' stays ON.
- if fault '1' and '4' is off/open connection  then all outputs 'A', 'B' and 'C' stays ON.
 

## Pin Assign
Reading or Input Pins detecting any signals from faulty
`A0 = Fault 1`
`A1 = Fault 2`
`A2 = Fault 3`
`A3 = Fault 4`
Note: 

Output for the outcome if any of the conditions are true
`A = Digital Pin 6`
`B = Digital Pin 7`
`C = Digital Pin 8`

**Note**:
- When any of the "fault" is being detected by the assigned pin inputs, there is a message displaying in the serial monitor "Fault n is detected!" where "n" is the specific number of fault is being detected
- In this prototype I implement a "Pull-up Resistor" then the code will modify accordingly

**Goal**:
- To make these following context instructions into a C++ Arduino Code
- To simulate the "Mesh/Ring Circuit" by using the Arduino UNO Development Kit Board



## Prototyping
This part will refine from the concept idea and will apply to prototyping in the Arduino UNO microcontroller development board.

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  bool fault1 = digitalRead(A0);
  bool fault2 = digitalRead(A1);
  bool fault3 = digitalRead(A2);
  bool fault4 = digitalRead(A3);

  if (fault1) Serial.println("Fault 1 is detected!");
  if (fault2) Serial.println("Fault 2 is detected!");
  if (fault3) Serial.println("Fault 3 is detected!");
  if (fault4) Serial.println("Fault 4 is detected!");

  if (fault1 && fault2) {
    Serial.println("Fault 1 and 2 is being detected!");
    digitalWrite(6, LOW);
  } else {
    digitalWrite(6, HIGH);
  }

  if (fault2 && fault4) {
    Serial.println("Fault 2 and 4 is being detected!");
    digitalWrite(7, LOW);
  } else {
    digitalWrite(7, HIGH);
  }

  if (fault3 && fault4) {
    Serial.println("Fault 3 and 4 is being detected!");
    digitalWrite(8, LOW);
  } else {
    digitalWrite(8, HIGH);
  }

  // Check for multiple faults
  if (fault1 && fault2 && fault3) {
    Serial.println("Fault 1, 2 and 3 is being detected!");
  }
  if (fault1 && fault2 && fault4) {
    Serial.println("Fault 1, 2 and 4 is being detected!");
  }
  if (fault1 && fault3 && fault4) {
    Serial.println("Fault 1, 3 and 4 is being detected!");
  }
  if (fault2 && fault3 && fault4) {
    Serial.println("Fault 2, 3 and 4 is being detected!");
  }
  if (fault1 && fault2 && fault3 && fault4) {
    Serial.println("Fault 1, 2, 3, and 4 is being detected!");
  }

  delay(1000); // Delay for stability
}
```

```cpp
// Pin definitions for fault inputs (using pull-up resistors)
// Pull-up resistors are used to ensure the input pins read HIGH when the switch is open
// This helps in detecting faults as an open connection will be read as HIGH
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
  // Read fault states (HIGH means fault/open connection due to pull-up)
  bool fault1 = digitalRead(fault1Pin) == LOW;
  bool fault2 = digitalRead(fault2Pin) == LOW;
  bool fault3 = digitalRead(fault3Pin) == LOW;
  bool fault4 = digitalRead(fault4Pin) == LOW;

  // Print fault detections to serial monitor
  if (fault1) Serial.println("Fault 1 is detected!");
  if (fault2) Serial.println("Fault 2 is detected!");
  if (fault3) Serial.println("Fault 3 is detected!");
  // Initialize output states to ON

  // Default state: all outputs ON
  bool stateA = true;
  bool stateB = true;
  bool stateC = true;

  // Check fault combinations and modify outputs accordingly
  if (fault1 && fault2) {
    stateA = false;  // Turn off output A
    Serial.println("Fault 1 and 2 are detected!");
    Serial.println("Output A is turned off!");
  } else if (fault2 && fault4) {
    stateB = false;  // Turn off output B
    Serial.println("Fault 2 and 4 are detected!");
    Serial.println("Output B is turned off!");
  } else if (fault3 && fault4) {
    stateC = false;  // Turn off output C
    Serial.println("Fault 3 and 4 are detected!");
    Serial.println("Output C is turned off!");
  } else {
    if (fault1) {
      Serial.println("Fault 1 detected!");
      Serial.println("Nothing Happens!");
    }
    if (fault2) {
      Serial.println("Fault 2 detected!");
      Serial.println("Nothing Happens!");
    }
    if (fault3) {
      Serial.println("Fault 3 detected!");
      Serial.println("Nothing Happens!");
    }
    if (fault4) {
      Serial.println("Fault 4 detected!");
      Serial.println("Nothing Happens!");
    }
    if (fault1 && fault3) {
      Serial.println("Fault 1 and 3 are detected!");
      Serial.println("Nothing Happens!");
    }
    if (fault1 && fault4) {
      Serial.println("Fault 1 and 4 are detected!");
      Serial.println("Nothing Happens!");
    }
    if (fault2 && fault3) {
      Serial.println("Fault 2 and 3 are detected!");
      Serial.println("Nothing Happens!");
    }
  }

  // Apply the output states
  digitalWrite(outputA, stateA ? HIGH : LOW);
  digitalWrite(outputB, stateB ? HIGH : LOW);
  digitalWrite(outputC, stateC ? HIGH : LOW);

  // Small delay to prevent serial port flooding
  delay(100);
}
```

```cpp
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
    Serial.println("Fault combination 2 and 3 detected! All outputs remain ON");
  }
  else if (fault1 && fault4) {
    Serial.println("Fault combination 1 and 4 detected! All outputs remain ON");
  }
  else if (fault1 && fault3) {
    Serial.println("Fault combination 1 and 3 detected! All outputs remain ON");
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
```
