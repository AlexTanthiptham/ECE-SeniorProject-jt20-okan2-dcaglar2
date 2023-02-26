#! DISCLAIMER THIS IS MY CODE FROM ECE395 AND HAVENT TESTED FOR STM32
#written by Okan Kocabalkanli
# Importing Libraries
import serial
import time

CR = b"\r"
NL = b'\n'
END_SIGNAL = b"\n\r"
class SerialCOM:
    def __init__(self,port='/dev/ttyAMA0', baudrate=115200, timeout=.1):
        self.arduino = serial.Serial(port=port,
        baudrate=baudrate,
        timeout=timeout,
        write_timeout=timeout,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE)
    def sendData(self,data:int):
        try:
            # data = bytes(str(data),encoding="utf8")
            # print(list(data),)
            print(f"you wrote: {data} nbytes: {self.arduino.write(serial.to_bytes([data]))}")
            self.arduino.flush()
        except ValueError:
            pass
    def readData(self):
        text= ""
        while True:
            data = self.arduino.read()
            # time.sleep(1)
            if data ==b'' or data == NL:
                continue
            if data ==CR:
                print(text)
                return text

            try:
                text += str(data,encoding="utf8")
            except UnicodeDecodeError:
                print(data)

arduino = SerialCOM(timeout=None)
text= ""
ihatelife=0
while ihatelife<10:
    # num = input("Enter a number: ") # Taking input from user
    #arduino.sendData(int(ihatelife))
    arduino.readData()
    ihatelife+=1
    time.sleep(2)
