#! DISCLAIMER THIS IS MY CODE FROM ECE395 AND HAVENT TESTED FOR STM32
#written by Okan Kocabalkanli
# Importing Libraries
import serial
import time
from math import pi
CR = b"\r"
NL = b'\n'
END_SIGNAL = b"\n\r"
class SerialCOM:
    def __init__(self,port='COM4', baudrate=115200, timeout=.1):
        self.arduino = serial.Serial(port=port,
        baudrate=baudrate,
        timeout=timeout,
        write_timeout=timeout,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE)
    def sendData(self,data):
        try:
            data = bytes(str(data)+"\n",encoding="utf8")
            #print(list(data))
            sentBytes = self.arduino.write(data)
            # print(f"you wrote: {data} nbytes: {sentBytes}")
            self.arduino.flush()
        except ValueError:
            pass
    def readData(self):
        text= ""
        
        while True:
            data = self.arduino.read()
            # time.sleep(1)
            #print("got",data)
            if data ==b'' or data == NL:
                continue
            if data ==CR:
                #print(text)
                return text

            try:
                text += str(data,encoding="utf8")
            except UnicodeDecodeError:
                print(data)
    def findCoords(self,rawStr:str)->tuple:
        leftIdx =  rawStr.find("(")
        rightIdx =  rawStr.find(")")
        newStr = rawStr[leftIdx+1:rightIdx]
        temp = newStr.split(",")
        # print(rawStr,temp)
        return (int(temp[0]),int(temp[1]),int(temp[2]),int(temp[3]))


if __name__ =="__main__":
    r= 3* 2.54
    l = 30
    rpmToVelocity = lambda rpm : (rpm/60) * (2*pi*r) 
    arduino = SerialCOM(port="/dev/ttyUSB0",timeout=None)
    text= ""
    ihatelife=0
    y= 30
    x=10
    count = 0
    xList =[]
    yList = []
    vlList = []
    vrList = []
    MAX_COUNT = 100
    from random import randint
    import matplotlib.pyplot as plt
    from robotModel import DifferentialDriveRobot
    robot = DifferentialDriveRobot(r,l)
    while True:
        # if count %10 ==0:
        #     y = randint(100,200)
        # randint(0,100)
        # num = input("Enter a number: ") # Taking input from user
        #arduino.sendData(int(ihatelife))
        #arduino.sendData(f"test-{ihatelife}")
        start = time.time()
        arduino.sendData(f"{x}|{y} ")
        ihatelife+=1
        # time.sleep(1)
        count+=1
        incomingData = arduino.readData()
        updatedIns = arduino.findCoords(incomingData)
        prevX= x
        prevY = y
        dt = time.time()-start#0.5#0.04#
        # v_l,v_r = rpmToVelocity(updatedIns[2]),rpmToVelocity(updatedIns[3])
        v_l, v_r = updatedIns[2],updatedIns[3]
        dx,dy,_ = robot.forward_kinematics(v_l,v_r,dt)
        print(f"vl:{v_l} vr:{v_r}, dx:{dx} dy:{dy} dt:{dt}")
        x += dx + randint(-2,2)
        y += dy + randint(-1,1)
        xList.append(x)
        yList.append(y)
        vlList.append(v_l)
        vrList.append(v_r)
        print(f"Update :{count} | x:{prevX}- {dx} ->{x} | y:{prevY}- {dy} ->{y}")
        if (count >MAX_COUNT):
            break
    # fig = plt.figure(figsize=(8, 6))
    # # Add the first subplot in the top row
    # ax1 = fig.add_subplot(2, 1, 1)

    # # Add the second subplot in the bottom row
    # ax2 = fig.add_subplot(2, 1, 2)
    # ax1.plot(range(0,len(yList)),yList,label="y-cont")
    # ax2.plot(range(0,len(xList)),xList,label="x-cont")
    plt.plot(range(0,len(yList)),yList)
    plt.savefig("yDistance.png")
    fig= plt.figure()
    plt.plot(range(0,len(xList)),xList)
    plt.savefig("xDistance.png")
        
"""
ser = serial.Serial ("/dev/ttyS0", 115200)    #Open port with baud rate
while True:

    data= ser.readline().decode().rstrip()
    if data:
        print(f'Recieved: {data}')

"""