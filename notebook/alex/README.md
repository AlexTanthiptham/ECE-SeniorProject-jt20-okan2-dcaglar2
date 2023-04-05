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

|V_out | R_2       |
|------|-----------|
|3.3 V | 220  Ohms |
|5 V   | 400  Ohms |
|12 V  | 1120 Ohms |

Identified design issue with main board design - MCU4 and MCU3 sockets are misaligned with breakout board configuration. Relative to the position of the MCU, these sockets are wired such that odd MCU pins are the outward facing row and even MCU pins are the inward facing row. This arangement is contrary to the breakout board and sockets MCU1 and MCU2 on the mainboard whereby odd pins are inward and even pins outward. 

Below is a simplified depiction of the misalignment. O representing odd pins and E representing even pins.

```
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
```

# Entry 10
Date: Apr 3, 2023

Minor Progress in Apr 2, 2023: Identified major design flaws during the course of attempting to debug inability to programming the MCU unit. This issue remains unresolved.

Identified Design Issues:
- (Breakout) VDD headers not connected to MCU VDD pins. Instead, MCU VDD pins are only connected to VDD_Target port of the programmer connector. 
- (Breakout) BOOT1, VDDUSB, VDDA, VREF+, VCAP_1 and VCAP_2 are not correctly connected, resulting in MCU start up issues.
- (Main) Breakout board intersects with voltage regulators, blocking connection of sockets to the board. 


In this session, the mainboard schematic was revised to address some design issues identified on Apr 2, 2023. In-depth review of STM32F423ZHT data sheet, application note and reference manual were made to seek a solution for inability to program MCU. Chiefly, the following ports were identified as being insufficiently connected: BOOT1, VDDUSB, VDDA, VREF+, VCAP_1 and VCAP_2.

As MCU specific components, these would be placed on the breakout board as per previous group design decisions. However,  due to expense of MCU units and risk of damage from de-soldering the unit, errors on the breakout board can only be resolved through adhoc means rather than PCB redesign and reprint. As such, these components are instead placed upon the main board and connected to the corresponding socket pins instead. Notable amongst these components is the case of VDDA. Owning to its need to be connected to the debouncing capacitor array to which other VDD pins (on breakout) are connected to, an additional manually soldered wire connetion between the mainboard and breakout board may be required to obtains its recommended wiring configuration.

Pending Main Board Tasks
- Realignment of sockets with breakout board header dimensions to adequet tolerances
- Rearrangement of components to resolve ECR warnings and errors
- Footprint selection & purchasing of newly added components 

# Entry 11
Date: Apr 5, 2023

Major design change. Began and completed revised KiCAD mainboard design schematic.

Change from STM32F423ZHT6 to STM32F401RBT6TR microcontroller. As our team must purchase all materials for the project out of pocket (due to My.ECE extreme unspecified issues), the continued purchase of STM32F423 in sufficient numbers to complete debugging and design revisions for this project has been deemed too great. 

Given the signficantly lower cost of STM32F401 microcontroller, the use of a breakout board was determined to no longer be economical. As such, in addition to software and hardware changes necessary in migrating from a 144-pin MCU to a 64-pin MCU, all breakout board components are also to be migrated over to the main board.

Progress Summary:
- Integrated breakout board components onto mainboard
- Removed breakout board sockets from mainboard
- Changed microcontrollers from STM32F423ZHT6 to STM32F401RBT6TR
- Added debugging features to main board 
     - Integrated switches for BOOT0 and BOOT1 values
     - GPIO ports for external 3.3, 5, 12V power supply

# Attribution
Format based on ECE445 Electronic Notebook guidelines and examples
https://gitlab.engr.illinois.edu/ece445/example-project