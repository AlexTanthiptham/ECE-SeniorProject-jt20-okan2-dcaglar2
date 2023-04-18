# Okan's Worklog

## 4/18/2023
### Goals
- Test out 3.3V and power the MCU using battery only.
- Turn on motors using the PCB MCU and battery.

### My Attempts
- Successfully set up the 3.3V LM voltage regulator.
- Programmed the board to generate 2 PWM signals and 4 GPIO outs.
- Controlled H-Bridge with PCB MCU.

### Issues Found
- While debugging, the 12V pin of the H-Bridge caused a short circuit with the MCU's timer pin, resulting in the MCU breaking.

### Achievements
- Created a working PCB that is programmable and solely powered on battery.

## 4/16/2023
### Goals
- Set up new buck converters.
- Power on the entire board with thermal efficiency.

### My Attempts
- Connected buck converters to the main power line to power 5V and the rest of the LMs.
- Dropped main 18V to 5V and 14V, respectively.

### Issues Found
- None.

### Achievements
- Buck converters and LM voltage regulators are operating without overheating.
- Successfully provided 12V and 5V to the systems.

## 4/14/2023
### Goals
- Find the issue that fried the dev-board.
- Program the PCB MCU.

### My Attempts
- Identified that the LM voltage regulators were becoming too hot.
- Ordered buck converters to power 5V and 3.3V.
- Successfully programmed the PCB MCU.

### Issues Found
- The LM voltage regulators were overheating, causing high current to pass through the dev-board.
- This caused the dev-board to draw 3A and get fried.

### Achievements
- Identified the issue with the dev-board.
- Ordered buck converters to overcome the issue.
- Successfully programmed the PCB MCU.

## 4/10/2023 - 4/12/2023
### Goals
- Assemble the robot using the dev-board and breadboards.
- Make the robot move straight for 5 seconds, then stop.

### My Attempts
- Used velcro to attach components to the robot.
- Powered the dev-board with an external power supply.
- Controlled the motor using a PWM signal from the dev-board.
- Controlled the motor using GPIO pins.
- Powered on the dev-board externally.

### Issues Found
- The dev-board was underpowered when powered with USB, causing the PWM and GPIO pins not to work correctly.
- The dev-board drew 3A when powered externally, leading to the whole board getting fried.

### Achievements
- Successfully controlled the motor using a PWM signal and GPIO pins.
- Powered on the dev-board externally.

## 4/13/2023 - 4/14/2023
### Goals
- Finish the remaining Kinect code.
- Get tilt data from the camera.
- Polish the current detection code for edge cases.
- Improve calibration for the Kinect.

### My Attempts
- Unit tested and patched edge cases on the current camera detecting code.
- Accessed tilt data.
- Created a new QR code with SHA256.

### Issues Found
- Due to using a Python wrapper, I don't have full access over the camera.
- Using a function called "runloop" can only be run every minute, which means we can only receive tilt data every minute.

### Achievements
- Accessed tilt data.
- Patched edge cases on the current camera detecting code.
- Created a new QR code with SHA256.
- Improved calibration for the Kinect.
## 4/10/2023- 4/14/2023
### Goals:
- Edited pcb design and ordering.
- Building electronic connections on the robot
- Trying to power the new motors.
### Achievements:
- Ordered new pcbs with new MCU.
- Robot electronic connections are finished

## 3/30/2023- 4/9/2023
### Goals:
- Try the new pcb
- Try the breakout board
### My Attempts:
- Soldering 
- Powering the breakout board
### Issues Found:
- Breakout board not powering
- Voltage regulators not working
## 3/25/2023 - 3/27/2023 
### Goals:
- Picked up robot from machine shop
- Finding new battery 
### My Attempts:
- Ordering 6V battery to take our input to 18V.
## PCB Design...
## Prototype ... 
## Machine shop talks...