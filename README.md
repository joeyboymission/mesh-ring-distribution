
# Mesh Ring Circuit Project

## Overview
A fault detection and output control system implemented on Arduino UNO for PSA Instrumentation course.

## Authors
- Lance Olaso
- Joey Boy Mission

## Hardware Requirements
- Arduino UNO
- 4 fault input switches (with pull-up resistors)
- 3 output devices (LEDs or relays)

## Pin Configuration
### Inputs (Fault Detection)
- Fault 1: Digital Pin 4
- Fault 2: Digital Pin 5
- Fault 3: Digital Pin 6
- Fault 4: Digital Pin 7

### Outputs
- Output A: Digital Pin 8
- Output B: Digital Pin 9
- Output C: Digital Pin 10

## Functionality
The system monitors four fault inputs and controls three outputs based on specific fault combinations:

### Fault Combinations and Effects
1. Fault 1 + Fault 2: Disables Output A
2. Fault 2 + Fault 4: Disables Output B
3. Fault 3 + Fault 4: Disables Output C
4. Fault 2 + Fault 3: Disables Outputs B and C
5. Fault 1 + Fault 4: Disables Outputs A and B
6. Fault 1 + Fault 3: Disables All Outputs (A, B, and C)

### Single Fault Behavior
Single faults do not affect the outputs - all outputs remain ON when only one fault is detected.

## Serial Communication
- Baud Rate: 9600
- Provides real-time fault detection status and output state information

## Operating Logic
1. All outputs are ON by default
2. System continuously monitors fault inputs
3. When fault combinations are detected, corresponding outputs are disabled
4. System includes a 100ms delay between iterations

## Note
The system uses internal pull-up resistors for fault inputs, meaning faults are detected when inputs are pulled LOW.