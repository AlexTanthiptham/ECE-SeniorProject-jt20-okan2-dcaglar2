from camera import Camera
import time
from uart import SerialCOM
import signal
import sys
from pdb import set_trace
import csv


data_list = []

def SIGINT_Handler(signum,frame) : 

    set_trace()

    with open("pid.csv","w",newline='') as csv_file: 

        writer = csv.writer(csv_file)

        writer.writerow(["X_OUT","Y_OUT","A_SPEED","B_SPEED","Y_DIST"])
        print(f"This is the final data_list: {data_list}")

        for data_point in data_list : 
            writer.writerow(data_point)

    sys.exit()


def parseCoords(rawStr:str) -> tuple: 
    leftIdx =  rawStr.find("(")
    rightIdx =  rawStr.find(")")
    newStr = rawStr[leftIdx+1:rightIdx]
    temp = newStr.split(",")
    # print(rawStr,temp)
    return [int(temp[0]),int(temp[1]),int(temp[2]),int(temp[3])]

signal.signal(signal.SIGINT,SIGINT_Handler)

if __name__ == '__main__':
    cam = Camera()
    print("Initializing Serial Connection...")
    arduino = SerialCOM(port="/dev/ttyUSB0",timeout=None,baudrate=9600)
    text= ""
    x,y=0,100
    prev= 0
    while True : 
        try:
            start = time.time()
            c = cam.update()
            print(f"Update took : {time.time() - start}")
            if c==None or c==0: continue
            else :
                x,y = int(c[0]),int(c[1])
        except Exception as error:
            print("Error")
            continue
        #if prev==c: continue
        print(c)
        start = time.time()
        arduino.sendData(f"{x}|{y}")
        #print(f" sending data took : {time.time() - start}")

        start = time.time()
        ret = arduino.readData()
        #print(f" receiving data took : {time.time() - start}")

        print(f"RET: {ret}")

        if "DATA" in ret : 
            start = time.time()
            coord_tup = parseCoords(ret)
            coord_tup.append(y)
            data_list.append(coord_tup)
            #print(f" parsing data took : {time.time() - start}")




            # time.sleep(1)
            #prev = c
            #res = ""

            #while "ACK" not in res:
            #    res = arduino.readData()
            #    print(f"GOT: {res}")
            #    continue

            #print(f"Received ACK at : {time.time() - start}")

            #arduino.sendData(f"ACK")

            #time.sleep(0.01)
