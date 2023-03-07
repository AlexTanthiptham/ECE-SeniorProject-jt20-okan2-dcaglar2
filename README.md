# ECE445 Final Project KiCAD
## Table of Contents
- [ ][PCBWAY-Checklist](#pcbway-checklist)
  - [ ][Schematic](#schematic)
  - [ ][Components](#components)
  - [ ][Printed Circuit Board](#printed-circuit-board)
- [To Do](#to-do)
  - [x][RPI](#rpi)
  - [x][Power](#power)
  - [x][Motors](#motors)
  - [x][LIDAR](#lidar)
  - [ ][Misc](#misc)
## PCBWAY-Checklist:

Before sending your PCB design to production, make sure to go through this checklist to avoid any potential problems or errors.

### Schematic

- [ ] How will you program the microcontroller? Does it have enough memory? Is it fast enough? Does the default bootloader let you program?
- [ ] Are any components being overvolted? What is the maximum operating voltage of your microcontroller?
- [ ] What voltage are your logic signals? Are your logic signals push/pull or open collector/drain? Do you have pull up/down resistors where needed?
- [ ] Are bypass capacitors placed properly? (watch a video tutorial if needed)
- [ ] Make your circuit easy to debug! Have you placed test points on key nodes? (Add a part > search “test point”. Edit symbol properties and select a footprint. Search “test point” in the footprint editor)
- [ ] If you are apprehensive about a chip not working, you can break out the pins into a row of headers (Search “Conn” in “Choose Symbol” window)
- [ ] Do you have a low-pass filter in front of any ADCs you are using? Even if you aren’t sure you need one, make one anyway. You can bridge over the resistor and remove the capacitor if you change your mind later.
- [ ] Have an external oscillator for the micro if you have timing requirements (either strict timing, or need timing over a long period of time). Also, know exactly what oscillator requirements your microcontroller needs
- [ ] Is there an easy way to power the circuit with a lab bench power supply? Having the ability to current limit your circuit while building and testing it is very useful. This can be as simple as having test points to solder leads to.

### Components

- [ ] Are connectors used OK for rated current? Take a look at “screw terminals” for external connections.
- [ ] Are barrel connectors correctly sized? They aren’t standardized well.
- [ ] Are components hard to solder? (QFN, BGA, etc. are really hard to solder because the pads are under the package)
- [ ] Are your SMD passive components too small? 0603 imperial (not metric!) are as small as you can feasibly hand-solder. 0805 is much easier.
- [ ] Does the footprint of what you bought/will buy match what you are using on your board? Ctrl-Shift-M to measure in the KiCAD PCB Editor
- [ ] Are your components in-stock?

### Printed Circuit Board

- [ ] Bypass/decoupling capacitors are placed next to ICs
- [ ] Proper trace widths. Ask how much current will be going through. A good metric is at least 20 mils for power and at least 10 mils for signal. If they have some high current paths, they may need to be more, though. (KiCAD project window > Calculator > Trace Width Calculator)
- [ ] No 90 degree bends! These produce a lot of noise.
- [ ] The maximum size your board can be is 100mm x 100mm
- [ ] No unrouted nets, no vias in pads
- [ ] Did you include mounting holes? How will the circuit mount to the rest of your project?
- [ ] Do you have a ground plane? Ground planes help reduce EMI
- [ ] Have you entered PCBway’s capabilities in the design rule checker? (6 mil minimum trace width/trace spacing; 0.3mm minimum hole size) (In PCB Editor File > Board Setup > Design Rules > Constraints
- [ ] Have you run a design rules check (DRC)?
- [ ] Do you know
## To Do:
### RPI:
- [x] Look into USB-C power delivery protocol for RPI connector
  - Maybe we should use just a connector and not usb-c
- [x] Add UART for pi Connector
- [x] Connect labels to MCU
### Power:
- [x] Look into power subsystem required battery connections (Capacitor, resistors)
- [x] Add decouple cap for power
- [x] Connect labels to MCU
- [x] Figure out how to power mcu
- [x] Kinect Power Connector
- [x] Battery Power Connector
### Motors:
- [x] Add symbol for Motor Controller Connector
- [x] Add labels
- [x] Motor power pin symb.
- [x] Stepper motor controller Connector (needs to be discussed)
  - Should we micro step? 
  - do we just want the bare minimum? 
  - Should we be safe? -> Use a 9 way connector
- [x] Connect labels to MCU
- [x] Motor output
- [x] Motor driver IC added 
- [x] Change the Motor adapter six pins for the encoder 
- [x] figure out how to connect encoder to the pcb
### LIDAR:
- [x] Add connector for lidar
- [x] Connect labels to MCU
### Misc:
- [x ] Find missing KiCAD part symbols/models (Listed on schematic)
- [x] How to attach programmer to mcu
  - NRST Pin
- [x] Programmer connector
- [x] Add pinout for free pins for debugging(OPT)
- [ ] Add LED to check power (OPT)
- [x] Connect caps closer. 
- [x] Find footprint for motor controller
- [ ] Check breakout sizing with the pcb
- [ ] Check board connections and power pins
- [x] Fix remaining warnings
- [ ] Add pins to top side of the breakout board


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




