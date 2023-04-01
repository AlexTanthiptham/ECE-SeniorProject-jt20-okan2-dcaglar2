# Alex Worklog

[[_TOC_]]

# Entry 1
Date: Feb 23, 2023

Authored and submitted final project design document, taking into account recommendations for changes to the proposal as well as additional details.

Changes made from proposal:
+ Moved app, bluetooth and obstacle detection components of existing subsystems to an addendum section as extensions to be made if time permits
+ Performed a full audit of all parts purchased, already present and checked out from lab for full cost analysis
+ Produced schedule of expected tasks in coordination with team members
+ Updated ethics and safety to reflect new changes to design (collision safety, replacement of lithium polymer battery with sealed lead acid battery)  

# Entry 2
Date: Feb 24, 2023 

Authored and submitted team contract.

# Entry 3
Date: Mar 1, 2023 

Design Decision: Due to difficulty of sourcing additional microcontrollers as well as the large number of mandatory soldered components (E.g. decoupling capacitors, pull up resistors), the MCU subsystem will be stored in a separate PCB board. Attached to the main board via a 2.54mm male header pins, handling the MCU as a separate, unaltered component allows for revisions to be made to other components of the main board without requiring time to repeatedly solder MCU requirements while also reducing the risk of damaging the MCU during board revisions.


Studied the STM32F767ZIT6 datasheet to produce breakout board schematic in KiCAD with appropriate wiring for all required components and pins. In addition to MCU-header connections, board also includes a separate header for programmer inputs as well as necessary pull up resistors and decoupling capacitors.

# Entry 4
Date: Mar 4, 2023 

Further refining of the breakout board, beginning the transition of the schematic to PCB. Begun arrangement of components, settling on a design with front mounted MCU and back mounted header pins and capacitors based on recommendations outlined in the MCU datasheet. Wiring of pins to components remains a WIP.

# Entry 5
Date: Mar 7, 2023 

Creation of a double-sided 2x18 2.54mm pin header footprint. Debugging to ensure dimensions of main board sockets and breakout board header pins are correctly aligned.

Progress: Fixed alignment issues (accurate up to +-0.0001 mm) and re-wired connections. This was done on the main board. No changes were made to the breakout board aside from the addition of a custom double sided 2x18 2.54mm header pin footprint. 

Remaining To Do: Lots of DRC errors & warnings from wires due to header socket move. Additional trouble shooting needed to ensure board complies with DRC. 

Note: Further moves to header pins are sockets are highly inadvisable 

# Entry 7
Date: Mar 28, 2023

Began soldering of PCB mainboard components. Assembled non-PCB power supply components: Soldered on battery connectors, PCB power connector cables and added an emergency stop switch to the power supply cable.

# Entry 8
Date: Mar 29, 2023

Verified LM1085-ADJ functionality, calculating required attached resistances to obtain the desired output voltage. Generally, measured output voltages trended lower than calculated values requiring adjustment of resistances to obtain the desired values. However, calculated resistance for 12V output unexpectedly resulted in an 18V output. Currently pending further examination of datasheet to identify this deviance from device specifications and trial/error of different resistances for a finalized value.

Current resistances: 200 Ohms for 3.3V output, 400 Ohms for 5V output, pending for 12V output.

Further assembled PCB mainboard components, soldering on various sockets and connectors arranged in a manner which allows for all components to be accessed without colliding with breakout board. Identified and fixed a LM1085 soldered in the wrong orientation during Mar 29.


# Entry 9
Date: Apr 1, 2023

Finalized LM1085-ADJ verification: 

200 Ohms for 3.3V output, 400 Ohms for 5V output, pending for 12V output.

Finalized LM1085-ADJ R2 resistances:

V_out ┃ R_2
──────╂──────────
3.3 V ┃ 220  Ohms
5 V   ┃ 400  Ohms
12 V  ┃ 1120 Ohms

Identified design issue with main board design - MCU4 and MCU3 sockets are misaligned with breakout board configuration. Relative to the position of the MCU, these sockets are wired such that odd MCU pins are the outward facing row and even MCU pins are the inward facing row. This arangement is contrary to the breakout board and sockets MCU1 and MCU2 on the mainboard whereby odd pins are inward and even pins outward. 

Below is a simplified depiction of the misalignment. O representing odd pins and E representing even pins.


        Main board       
           MCU4          
          O O O
          E E E
      E O       E O
MCU1  E O       E O   MCU3
      E O       E O
          O O O
          E E E
           MCU2

      Breakout board       
           MCU4          
          E E E
          O O O
      E O       O E
MCU1  E O       O E   MCU3
      E O       O E
          O O O
          E E E
           MCU2


# Attribution
Format based on ECE445 Electronic Notebook guidelines and examples
https://gitlab.engr.illinois.edu/ece445/example-project
