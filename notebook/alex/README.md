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

# Entry 4
Date: Mar 7, 2023 
Creation of a double-sided 2x18 2.54mm pin header footprint. Debugging to ensure dimensions of main board sockets and breakout board header pins are correctly aligned.

# Attribution
Format based on ECE445 Electronic Notebook guidelines and examples
https://gitlab.engr.illinois.edu/ece445/example-project
