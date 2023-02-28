# ECE445 Final Project KiCAD


## To Do:
### RPI:
- [ ] Look into USB-C power delivery protocol for RPI connector
  - Maybe we should use just a connector and not usb-c
- [x] Add UART for pi Connector
- [x] Connect labels to MCU
### Power:
- [ ] Look into power subsystem required battery connections (Capacitor, resistors)
- [ ] Add decouple cap for power
- [ ] Connect labels to MCU
- [ ] Figure out how to power mcu
- [ ] Kinect Power Connector
- [ ] Battery Power Connector
### Motors:
- [x] Add symbol for Motor Controller Connector
- [x] Add labels
- [x] Motor power pin symb.
- [x] Stepper motor controller Connector (needs to be discussed)
  - Should we micro step? 
  - do we just want the bare minimum? 
  - Should we be safe? -> Use a 9 way connector
- [x] Connect labels to MCU
- [ ] Motor output
- [ ] add jumper
### LIDAR:
- [x] Add connector for lidar
- [x] Connect labels to MCU
### Misc:
- [ ] Find missing KiCAD part symbols/models (Listed on schematic)
- [ ] How to attach programmer to mcu
  - NRST Pin
- [x] Programmer connector
- [ ] Add footprint to all connectors
- [ ] Add pinout for free pins for debugging(OPT)
- [ ] Add LED to check power (OPT)


## Questions:
1) What connector to use
2) Can I use usb-c as UART and power at the same time
3) 
## Reference Images:
### Block Diagram
![block diagram](Block%20Diagram.png)
### MCU :
https://www.st.com/content/ccc/resource/technical/document/datasheet/group3/c5/37/9c/1d/a6/09/4e/1a/DM00273119/files/DM00273119.pdf/jcr:content/translations/en.DM00273119.pdf

### Stepper Diagram:
![stepper](https://a.pololu-files.com/picture/0J10459.1200.jpg?6038e21c689b2e1cca6f39d4204c96f7)
### Motor Diagram:


### RPI:
![rpi](https://www.raspberrypi.com/documentation/computers/images/GPIO-Pinout-Diagram-2.png)




