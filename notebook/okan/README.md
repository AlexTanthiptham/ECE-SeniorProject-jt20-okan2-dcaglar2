# Okan's Worklog
## 4/27/2023 - 5/2/2023
### Goals:
- Collect data for presentation
- Add a logger system to the RPI to collect step response data
### My attempts:
- Attempted to reshape the shaft by heating it up
- Decided to take the shaft to a machine shop
### Issues encountered:
- The wheel shaft broke
- After reassembling the robot, two PCBs blew
### Achievements:
- Successfully recorded a graph response of the PID systems while the robot was fully functional

## 4/25/2023 - 4/26/2023
### Goals:
- Add Speed Control PID
- Update Y Controller PID
- Update X Controller PID
### My attempts:
- Attempted PID using Encoder as feedback to Speed Control PID
- Attempted using only Ki for Speed Control PID
- Attempted using only P for Y & X Controllers
- Attempted using high Ki and low Kd and Kp for Y & X Controllers
### Issues encountered:
- Y PID Controller had trouble stopping
### Achievements:
- Robot can follow QRCode but has trouble stopping at steady state.

## 4/24/2023
### Goals:
- Close the robot permanently
- Run robot tests with new PID
- Obtain accurate data from encoders
### My attempts:
- Created a virtual PID training ground (look at uart.py in RPI branch)
- Trained Y-Controller
### Issues encountered:
- The noise generated by the virtual training ground underestimated real noise, making the system more vulnerable than anticipated
### Achievements:
- Trained PID fully virtually
- The robot somewhat follows the QRCode

## 4/19/2023 - 4/22/2023
### Goals:
- Remake a PCB
- Add Y Controller PID
- Add X Controller PID
- Close the robot permanently
- Figure out how the encoder works
### My attempts:
- Programmed the Y Controller in firmware
- Programmed the X Controller in firmware
- Transferred components from the old (dead) PCB to the new PCB
### Issues encountered:
- The cables were still risky, so they needed to be soldered
- The encoder datasheet was incorrect, so each wire had to be probed to determine the encoder with an oscilloscope
### Achievements:
- Made the robot move
- Obtained data from encoders

### Goals:
- Test out 3.3V and power the MCU using battery only
- Turn on motors using the PCB MCU and battery
### My attempts:
- Successfully set up the 3.3V LM voltage regulator
- Programmed the board to generate 2 PWM signals and 4 GPIO outs
- Controlled H-Bridge with PCB MCU
### Issues encountered:
- While debugging, the 12V pin of the H-Bridge caused a short circuit with the MCU's timer pin, resulting in the MCU breaking
### Achievements:
- Created a working PCB that is programmable and solely powered by battery
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