# Robot-Avoider

**Robot Avoider using HC-SR04** is an **obstacle-avoiding robot** that uses the **HC-SR04 ultrasonic sensor** to detect objects and automatically avoid collisions.

### Brief explanation

The HC-SR04 ultrasonic sensor works by:

1. Sending ultrasonic sound waves (40 kHz)
2. The waves hit an object and reflect back
3. The sensor receives the echo
4. Distance is calculated based on the travel time of the sound wave

Distance formula:

Distance=Time×Speed of Sound2\text{Distance} = \frac{\text{Time} \times \text{Speed of Sound}}{2}

Distance=2Time×Speed of Sound

### How the robot works

1. The HC-SR04 measures the distance in front of the robot
2. **If the distance is greater than a preset threshold** → the robot moves forward
3. **If the distance is less than or equal to the threshold** → the robot stops
4. The robot then:
    - Turns left or right, or
    - Moves backward and searches for a clear path

### Main components

- **HC-SR04 ultrasonic sensor**
- **Microcontroller** (Arduino, ESP32, etc.)
- **DC motors with motor driver** (L298N, L293D)
- **Power supply / battery**
- Robot chassis

### Function & applications

- Learning **basic robotics**
- **Embedded systems** and **IoT** projects
- Introduction to **autonomous navigation**
- Educational and research robots
