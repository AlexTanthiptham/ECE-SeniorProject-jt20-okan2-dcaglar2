from camera import Camera
import time
from uart import SerialCOM



if __name__ == '__main__':
    cam = Camera()
    print("Initializing Serial Connection...")
    arduino = SerialCOM(port="/dev/ttyUSB0",timeout=None)
    text= ""
    x,y=0,100
    while True : 
        try:
            c = cam.update()
            print(c)
            if c==None or c==0: continue
            x,y = int(c[0]),int(c[1])
        except Exception as error:
            continue
            print("Error")
        print(f"Sending Serial Data {x}|{y}")
        arduino.sendData(f"{x}|{y}")
        # time.sleep(1)
        print("GOT:",arduino.readData())
