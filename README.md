# Car Parking System Using Arduino

An automated car parking management system built with Arduino that monitors parking slots, controls entry/exit barriers, and displays real-time availability on an LCD screen.

## Features

- **Real-time Slot Monitoring**: Tracks 3 parking slots using IR sensors
- **Automated Barrier Control**: Servo motor-controlled entry/exit gate
- **LCD Display**: Shows available slots and individual slot status
- **Smart Entry/Exit Logic**: Prevents entry when parking is full
- **Slot Counter**: Automatically updates available parking spaces

## Hardware Components

- **Arduino Board** (Uno/Nano recommended)
- **Servo Motor** - Controls the parking barrier
- **LCD Display (16x2)** with I2C module (Address: 0x27 or 0x3F)
- **5x IR Sensors**:
  - 1x Entry sensor
  - 1x Exit sensor
  - 3x Parking slot sensors
- **Jumper wires** and **Breadboard**
- **Power Supply** (5V)

## Pin Configuration

| Component        | Arduino Pin |
| ---------------- | ----------- |
| Entry IR Sensor  | Pin 2       |
| Exit IR Sensor   | Pin 3       |
| Servo Motor      | Pin 4       |
| Slot 1 IR Sensor | Pin 5       |
| Slot 2 IR Sensor | Pin 6       |
| Slot 3 IR Sensor | Pin 7       |
| LCD (I2C)        | SDA & SCL   |

## Circuit Diagram

```
Arduino
├── Pin 2  → IR Entry Sensor
├── Pin 3  → IR Exit Sensor
├── Pin 4  → Servo Motor (Signal)
├── Pin 5  → IR Slot 1 Sensor
├── Pin 6  → IR Slot 2 Sensor
├── Pin 7  → IR Slot 3 Sensor
├── SDA    → LCD I2C (SDA)
└── SCL    → LCD I2C (SCL)
```

## Required Libraries

Install the following libraries via Arduino IDE Library Manager:

- `Servo.h` - Built-in Arduino library
- `Wire.h` - Built-in Arduino library
- `LiquidCrystal_I2C.h` - [Download here](https://github.com/johnrickman/LiquidCrystal_I2C)

## Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/YousefElbilkasy/Parking-System-Using-Arduino.git
   ```

2. Open `Parking.ino` in Arduino IDE

3. Install required libraries (see above)

4. Connect your Arduino board via USB

5. Select the correct board and port:

   - Tools → Board → Arduino Uno (or your board)
   - Tools → Port → (select your COM port)

6. Upload the code to your Arduino

## How It Works

### System Logic

1. **Initialization**:

   - System boots with welcome message
   - Reads initial slot occupancy
   - Sets barrier to closed position (97°)

2. **Entry Process**:

   - Car approaches entry sensor
   - If slots available: barrier opens (7°), counter decreases
   - If parking full: displays "Sorry Parking Full"

3. **Exit Process**:

   - Car approaches exit sensor
   - Barrier opens (7°), counter increases
   - Barrier closes after car passes

4. **Slot Monitoring**:
   - Continuously monitors all 3 parking slots
   - Updates LCD display in real-time
   - Shows "F" (Full) or "E" (Empty) for each slot

### LCD Display Format

```
Line 1: Have Slots: X
Line 2: S1:E S2:F S3:E
```

- `X` = Number of available slots (0-3)
- `E` = Empty slot
- `F` = Full slot

## Customization

### Change Total Slots

```cpp
int slot = 3;  // Modify this value (line 23)
```

### Adjust Servo Angles

```cpp
myservo.write(97);  // Closed position
myservo.write(7);   // Open position
```

### LCD I2C Address

If your LCD doesn't display anything, try changing the address:

```cpp
LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Try 0x3F instead of 0x27
```

## Troubleshooting

| Issue                 | Solution                                             |
| --------------------- | ---------------------------------------------------- |
| LCD shows nothing     | Check I2C address (0x27 or 0x3F), verify connections |
| Servo not moving      | Check power supply, verify pin connection (Pin 4)    |
| Wrong slot count      | Verify IR sensor placement and wiring                |
| Barrier doesn't close | Check flag logic, ensure sensors detect car passage  |

## Project Structure

```
Parking-System-Using-Arduino/
├── Parking.ino          # Main Arduino sketch
└── README.md           # This file
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is open source and available for educational purposes.

## Author

**Yousef Elbilkasy**

## Acknowledgments

- Arduino community for libraries and support
- Embedded Systems course project

---

**Note**: This is an educational project. For production use, consider adding error handling, sensor calibration, and fail-safe mechanisms.
