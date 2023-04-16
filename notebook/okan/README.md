# Okan Worklog
## 4/16/2023
## 4/14/2023
### Goals:
- Find the issue that fried the devboard
- Program the pcb MCU

### My Attempts:
- Identified that the LM voltage regulators were becoming too hot
- Ordered buck converters to power 5V and 3.3V
- Successfully programmed the pcb MCU

### Issues Found:
- The LM voltage regulators were becoming too hot, leading to passing high current to the devboard
- This caused the devboard to draw 3A and fried the whole board

### Achievements:
- Identified the issue with the devboard
- Ordered buck converters to overcome the issue
- Successfully programmed the pcb MCU

## 4/10/2023 - 4/12/2023
### Goals:
- Assemble the robot using dev-board and breadboards
- Make the robot move straight for 5 seconds then stop

### My Attempts:
- Used velcros to attach components to the robot
- Powered the devboard with external power supply
- Controlled motor using pwm signal from the devboard
- Controlled motor using GPIO pins
- Powered on the devboard externally

### Issues Found:
- Devboard was under-powered when powered with USB, leading to pwm and GPIO pins not working correctly
- Devboard drew 3A when powered externally, leading to the whole board getting fried

### Achievements:
- Successfully controlled motor using pwm signal and GPIO pins
- Powered on the devboard externally

## 4/13/2023 - 4/14/2023
### Goals:
- Finish remaining Kinect Code
- Get tilt data from the camera
- Polish current detection code for edge cases
- Improve calibration for the Kinect

### My Attempts:
- Unit tested and patched edge cases on current camera detecting code
- Accessed tilt data
- Created new QR code with sha256

### Issues Found:
- Due to using a Python wrapper, I don't have full access over the camera
- Using a function called "runloop" can only be run every minute, which means we can only receive tilt data every minute

### Achievements:
- Accessed tilt data
- Patched edge cases on current camera detecting code
- Created new QR code with sha256
- Improved calibration for the Kinect


## Old ones will be added later...