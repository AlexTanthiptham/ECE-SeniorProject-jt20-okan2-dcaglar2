# PCB Design Stuff
- Added the motor driver IC and its peripherals to the PCB
- Using L298N with two motors
- Desoldered the H-bridge IC from the board it came with and soldered onto main board.
- Changed the voltage regulator that we were using to an adjustable one

- Redrew connections on main board due to redesign. Thermal and fill errors present

- We moved on to a new chip and completely redesigned the board. The new board does not use a secondary breakout board and has the MCU together with the voltage control circuits. We also picked a smaller MCU chip that has 64 pins instead of the 144 pins that came with our earlier MCU.

- As the new PCB was being built we tried to get our motors running with our current devboard. We fully built out the robot and mounted everything on top of the chassis.

- We made all electrical connections  and used our 12V and 5V regulators to power our devboard and motors.

- After limited operation time where everything worked fine, we observed a flash and smoke. After hitting our emergency stop we saw that we had fired our devboard.
    - After close inspection it seemed that the voltage regulators and current limiters on the board were fried.
    - We also observed that our linear voltage regulators were incredibly hot right after this event.
    - We suspected that we could have supplied our MCU with unregulated voltage our current due to a part of the voltage regulator failing in some way.
    - After some consideration and experimentation with different loads (10,30,50,100,1k,10k ohms), we saw that we were unable to pull the required current from our 5V regulator without generating too much heat that the unit failed to properly regulate the voltage or the current.
    - With some simple calculations we saw that our regulators were dropping down from ~18-19V to 5V where we attempted to draw 500mA of current which means that we generated ~6-7W of heat consistently.
    - This was not doable with our current cooling setup.
    - When we account for the fact that we're gonna hook up our Raspberry Pi to our 5V regulators which is known to draw up to 2A of current, we would be generating approximately 26W of heat!
    - Due to these reasons we decided to change our regulators to be buck converters instead of linear regulators as buck converters have increased efficiency while delivering higher current loads.

