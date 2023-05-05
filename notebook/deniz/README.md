
# Electrical Work (Soldering, wiring)

- Since our motors still haven't arrived we found two replacement motors from the lab and soldered new leads to start testing our PID logic

- We have ordered replacement motors, they have arrived and been delivered to the machine shop

- Due to battery drop out on voltage regulators we went with a serial battery setup with one 12V and one 6V battery. The connections from the battery to the emergency stop and start switches have been made

- The SMD components have been soldered on the main board.

- The THT voltage regulators have been soldered on the main board.

- We finished soldering the main board, however the MCU proved to have too thin pins to use a stencil with, as the solder paste leaked off the pads and smeared everywhere.

    - Due to this we tried soldering the MCU by hand, during which we bent multiple pins and couldn't align it properly.
    - We soldered our other MCU with the help of a friend which showed us a better technique.

- We tried connecting to this MCU with our ST-Link. However, we couldn't program it from the STM32CubeIDE. We tried using the lower level STM32 Programmer utility, which enabled us to see the internal memory and registers of the chip.
    - The chip turned out to have something wrong with it as we couldn't read any memory from it without resetting for each memory read. 
    - We realized that one of the flash memory control registers of the chip had its read protection bit enabled, where this bit protection bit should have been disabled by default.
    - We read the manual and employed the unlocking combinations to be able to change the read protection bit value. This wouldn't change the read protection bit permanently.
    - We realized that the reason the read protection bit was enabled was because of our boot configuration picked by our BOOT0,BOOT1 pins.
    - We altered the BOOT0,BOOT1 pins to the correct configuration however the internal resistors of the MCU wouldn't show this change and would just boot in locked mode.
    - After talking to a more experienced friend, we learned that our MCU drawing ~30-40mA from the lab power supply was a bad sign as its only supposed to draw ~1-2mA.
    - We concluded that we had fried some part of the MCU and moved on to a new model.

- Our new PCB's have arrived and we managed to successfully program our chip on the first try. It works!

    
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

- We experienced setbacks due to our MCU and Raspberry Pi getting out of sync while communicating over UART. We hypothesized that this could be due to the XBox Kinect not being a real-time system and having no processing time guarantees.
    - This meant that it was possible that the Kinect would cause the UART connections to go out of sync due to packets not being ready in 22:49
    - We ended up fixing this by decreasing our baudrate from ~115200 to ~9600.
    

# Physical Building Progress

- Had initial meeting with the machine shop where we talked about the possiblity of getting a prebuilt chassis and discussed the division of cost when building the robot

- Visited the machine shop again and picked up a preexisting chassis built for a nother project. Designed CAD to further extend the chassis for our purposes.

- Finalized the design and talked to the machine shop once more to get construction started 

- Waiting on all mechanical parts to arrive to drop everything by the machine shop 

- Talked to the machine shop to get a quote for all construction processes. They quoted 8 hrs/day for 4 days of construction time for our robot.

- The replacement motors arrived and got dropped off at the machine shop

- Picked up the motors from the machine shop, the lower layer of the robot is finished, will add kinect and railings ontop.

- Added our on/off switch to our robot, we chiseled the top wooden layer to create a lower depth then the rest of the surface which was required when mounting our switch. 

- We then drilled some mounting holes on our aluminum lower layer to fasten our main components such as our battery,pcb and breadboard for temporary operations.

- We also employed zip ties and double sided velcro tape to ensure stability for our main components.

- Our next step will be putting on our Xbox Kinect at the front

# RPI Progress

- Initially looked for a bluetooth library to setup on the RPI with Okan

- Gave up on the bluetooth idea since we were able to checkout the Kinect from the lab. 

- Setup OpenCV and libfreenect on the RPI with Python 3.7 with Okan

- Converted our preexisting code to work with libfreenect to read distance and recognize a QR code from our RPI with Okan

- We came upon a problem where the kinect would not be able to detect and decode QR codes due to the tilt angle of the kinect and the kinect on a much lower altitude than the QR code that its trying to read.
    - We fixed this problem by employing a warp perspective algorithm that flipped the perspective on the Kinect image so that the QR code would be detectable

