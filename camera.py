import freenect
import math
import numpy as np
CALIBRATION_DISTANCE = 1 #meter
QR_CODE_REAL_WIDTH = 0.21#m
def distanceBetweenTwoPoints(point1,point2):
    """Calculate the Euclidean distance between two points."""
    dx = point2[0] - point1[0]
    dy = point2[1] - point1[1]
    return math.sqrt(dx**2 + dy**2)
class Camera:
    def __init__(self) -> None:
        self.focalLength = None
        try: 
            with open("calibration.txt","w") as f:
                self.focalLength = float(f.read())
        except Exception as error:
            print(error)
            self.calibrate()
        self.CentrePoint= (240,320) #480,640 /2 = 240,320
    def getTiltAngle(self)->int:
        return 0 #rad
    def getFrame(self):
        return []
    def getDepth(self):
        return []
    def detectQRCode(self,img):
        #Deniz's qr code vvvvv
        QRimg = np.array([])
        points = []
        return QRimg,points
    def calibrate(self):
        #turn on led 
        # finding the focal length
        while True:
            print(f"Place QR code {CALIBRATION_DISTANCE} meter away from Kinect and then hit any key to continue")
            input()
            QRCodeImg,points = self.detectQRCode(self.getFrame())
            if QRCodeImg != None:
                break
        referenceImgWidth =  QRCodeImg.shape[1]# in pixels
        self.focalLength = (referenceImgWidth * CALIBRATION_DISTANCE) / QR_CODE_REAL_WIDTH
        with open("calibration.txt","w") as f:
            f.write(str(self.focalLength))
    def searchForQRCode(self):
        frame,depth = self.getFrame(),self.getDepth()
        QRCodeImg,points = self.detectQRCode(frame)
        #vvvv crop code
        QRCodeDepthImg = []
        return QRCodeImg,QRCodeDepthImg,points
        


    def CalculateVectorDistance(self,depthImg):
        distance = 0.0 #m
        #deniz's depth calc code vvvvv
        return distance

    def CoordinateDistanceCalc(self,depthImg,topLeftPoint:tuple):
        if(self.focalLength==None):
            raise Exception("Calibration Error Please Calibrate Device")
        vectorDistance  = self.CalculateVectorDistance(depthImg) #this is what we detect
        kinectPlaneDistance = vectorDistance * math.cos(self.getTiltAngle()) # this is the distance on kinects plane aka ground
        distanceToCentreInX = topLeftPoint[0] - self.CentrePoint[0]  
        width = depthImg.shape[1]
        xdistance = (QR_CODE_REAL_WIDTH*self.focalLength)/distanceToCentreInX
        ydistance = math.sqrt(vectorDistance**2 - xdistance**2)
        return (xdistance,ydistance)
        #@TODO: auto calibartion with ydistance estimate and real value from a^2+b^2 = c^2.
        
        


    def update(self):
        QRCodeImg,QRCodeDepthImg,points =self.searchForQRCode()
        print(self.CoordinateDistanceCalc(QRCodeDepthImg,points[0]))



if __name__ == '__main__':
    kinect = Camera()
    while True:
        kinect.update()




