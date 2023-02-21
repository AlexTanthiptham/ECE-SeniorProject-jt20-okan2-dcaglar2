import freenect
import math
import numpy as np
import cv2
CALIBRATION_DISTANCE = 1 #meter
QR_CODE_REAL_WIDTH = 0.21#m
KERNEL_SIZE=(17,17)
X_STD=0
qrDecoder = cv2.QRCodeDetector()
def distanceBetweenTwoPoints(point1,point2):
    """Calculate the Euclidean distance between two points."""
    dx = point2[0] - point1[0]
    dy = point2[1] - point1[1]
    return math.sqrt(dx**2 + dy**2)
class Camera:
    def __init__(self) -> None:
        self.focalLength = None
        try: 
            with open("calibration.txt","r") as f:
                self.focalLength = float(f.read())
        except Exception as error:
            print(error)
            self.calibrate()
        self.CentrePoint= (240,320) #480,640 /2 = 240,320
    def getTiltAngle(self)->int:
        freenect.getTiltAngle()
        print(freenect.getTiltAngle())
        return 0 #rad
    def getFrame(self):
        array,_ = freenect.sync_get_video()
        array = cv2.cvtColor(array,cv2.COLOR_RGB2BGR)
        #array = cv2.GaussianBlur(array,KERNEL_SIZE,X_STD)
        return array
    def getDepth(self):
        array,_ = freenect.sync_get_depth() 
        array = array / 10.0
        array = cv2.GaussianBlur(array,KERNEL_SIZE,X_STD)
        return array
    def detectQRCode(self,frame):
        # detect qr code
        data,points,rectifiedImage = qrDecoder.detectAndDecode(frame)
        qr_code_img = []
        # check if points are found
        #if data != '':
        try: 

            top_left = points[0][0]
            top_right = points[0][1]
            bot_right = points[0][2]
            bot_left = points[0][3]

            y_range = [int(top_left[1]),int(bot_left[1])]
            x_range = [int(top_left[0]),int(top_right[0])]

            qr_code_img = frame[ y_range[0]:y_range[1], x_range[0]:x_range[1]]
            cv2.imshow("QRCode",qr_code_img)

        except Exception as error: 
            #print(error)
            pass
        return qr_code_img,points
    def calibrate(self):
        #turn on led 
        # finding the focal length
        while True:
            print(f"Place QR code {CALIBRATION_DISTANCE} meter away from Kinect and then hit any key to continue")
            input()
            QRCodeImg,points = self.detectQRCode(self.getFrame())
            if QRCodeImg.all() != None:
                break
        referenceImgWidth =  QRCodeImg.shape[1]# in pixels
        self.focalLength = (referenceImgWidth * CALIBRATION_DISTANCE) / QR_CODE_REAL_WIDTH
        print(self.focalLength)
        with open("calibration.txt","w") as f:
            f.write(str(self.focalLength))
    def searchForQRCode(self):
        frame,depth = self.getFrame(),self.getDepth()
        QRCodeImg,points = self.detectQRCode(frame)
        QRCodeDepthImg = np.array([])
        try : 
            top_left = points[0][0]
            top_right = points[0][1]
            bot_right = points[0][2]
            bot_left = points[0][3]

            y_range = [int(top_left[1]),int(bot_left[1])]
            x_range = [int(top_left[0]),int(top_right[0])]
       
            QRCodeDepthImg  = depth[y_range[0]:y_range[1],x_range[0]:x_range[1]]
            print(QRCodeDepthImg)
        except Exception as error:
            print(error)
            pass
        return QRCodeImg,QRCodeDepthImg,points
        


    def CalculateVectorDistance(self,depthImg):
        distance = 0.0 #m
        #deniz's depth calc code vvvvv
        QRCodeDepthImg = depthImg.flatten()
        distance = int(np.average(QRCodeDepthImg))
        print("vector",distance)
        return distance

    def CoordinateDistanceCalc(self,depthImg,topLeftPoint:tuple):
        if(self.focalLength==None):
            raise Exception("Calibration Error Please Calibrate Device")
        vectorDistance  = self.CalculateVectorDistance(depthImg) #this is what we detect
        if(vectorDistance ==0):
            return 0
        kinectPlaneDistance = vectorDistance * math.cos(self.getTiltAngle()) # this is the distance on kinects plane aka ground
        distanceToCentreInX = topLeftPoint[0] - self.CentrePoint[0]  
        width = depthImg.shape[1]
        xdistance = (QR_CODE_REAL_WIDTH*self.focalLength)/distanceToCentreInX
        ydistance = math.sqrt(vectorDistance**2 - xdistance**2)
        return (xdistance,ydistance)
        #@TODO: auto calibartion with ydistance estimate and real value from a^2+b^2 = c^2.
        
        


    def update(self):
        QRCodeImg,QRCodeDepthImg,points =self.searchForQRCode()
        if(QRCodeDepthImg.shape[0] == 0):
            return
        print(QRCodeDepthImg.shape)
        print(self.CoordinateDistanceCalc(QRCodeDepthImg,points[0][0]))



if __name__ == '__main__':
    kinect = Camera()
    while True:
        kinect.update()




