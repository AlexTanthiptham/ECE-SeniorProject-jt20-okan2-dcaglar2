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

    
