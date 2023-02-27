# ECE445 Final Project

## MCU Code

## Todo

- [ ] Transfer Kinect data via UART
- [ ] Proper kinect calibration
- [ ] PID parameter training
- [x] Fix Lidar bug so it doesn't die after one measurement

## Working So Far

- Motor driver can go forward and back with variable speed
- UART can print
- LIDAR can read data
- Can talk to RPi (minimally)
- PID controller is initialised

### UART Print Console Instructions

1. Open Putty with the write COM port (For Windows, look at Device Manager).
2. Click Serial and set the baud rate to 115200.
3. It should work!
