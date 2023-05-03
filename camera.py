import freenect
import math
import numpy as np
import cv2
from cache import CacheManager
from time import time
from pdb import set_trace
CALIBRATION_DISTANCE = 1 #meter
QR_CODE_REAL_WIDTH = 0.21#m
KERNEL_SIZE=(17,17)
RESIZE = 800
X_STD=0
DEBUG = False
qrDecoder = cv2.QRCodeDetector()
def distanceBetweenTwoPoints(point1,point2):
    """Calculate the Euclidean distance between two points."""
    dx = point2[0] - point1[0]
    dy = point2[1] - point1[1]
    return math.sqrt(dx**2 + dy**2)

def timeIt(func):
    def wrap(*args,**kwargs):
        start = time()
        ret = func(*args,**kwargs)
        print(f"{func.__name__} took: {time() - start}")
        return ret
    return wrap
def mes(t,name):
    #print(f"{name} took {time()-t}" )
    return time()
class Camera:
    #@timeIt
    def __init__(self) -> None:
        
        self.cm = CacheManager() 
        self.focalLength = self.cm.getFocalLength()
        self.kdc = self.cm.getKinectDistanceCal() # multiply this with vector dist
        if self.focalLength == None:
            self.calibrate()
        self.CentrePoint= (240,320) #480,640 /2 = 240,320
        self.tiltAngle = np.deg2rad(24)
#        self.startLoop = True
 #       freenect.runloop(body=self.__tiltUpdateSequence)
  #      while self.startLoop:
   #         pass
    def getTiltAngle(self)->int:
        return self.tiltAngle
    #@timeIt
    def getFrame(self):
        array,_ = freenect.sync_get_video()
        array = cv2.cvtColor(array,cv2.COLOR_RGB2GRAY)
        #array = cv2.resize(array,(RESIZE,RESIZE),interpolation=cv2.INTER_AREA)
        #array = cv2.GaussianBlur(array,KERNEL_SIZE,X_STD)
        return array
    #@timeIt
    def getDepth(self):
        t= time()
        array,_ = freenect.sync_get_depth() 
        t= mes(t,"get s")
        array = array / 10.0 #to cm
        t= mes(t,"dvd")
        #array = cv2.resize(array,(RESIZE,RESIZE),interpolation=cv2.INTER_AREA)
        array = cv2.GaussianBlur(array,KERNEL_SIZE,X_STD)
        t= mes(t,"blur")
        return array
    def decode(self,QRcodeImg,points):
        data = qrDecoder.decode(QRcodeImg,points)
        return data
    def calibrate(self):
        #turn on led 
        # finding the focal length
        while True:
            print(f"Place QR code {CALIBRATION_DISTANCE} meter away from Kinect and then hit any key to continue")
            input()
            # frame,depth = self.getFrame(),self.getDepth()
            # QRCodeImg,points = self.detectQRCode(frame)
            # _,points = qrDecoder.detect(frame)
            # if QRCodeImg.all() != None:
            QRCodeImg,QRCodeDepthImg,points =self.searchForQRCode()
            if points is None:
                continue
            try:
                set_trace()
                referenceImgWidth =  QRCodeImg.shape[1]# in pixels
                self.focalLength = (referenceImgWidth * CALIBRATION_DISTANCE) / QR_CODE_REAL_WIDTH
                print("fl",self.focalLength)
                self.cm.setFocalLength(self.focalLength)
                print(QRCodeDepthImg)
                self.kdc = 1
                estimatedDist = self.CalculateVectorDistance(QRCodeDepthImg)
                print("est-d:",estimatedDist)
                self.kdc = CALIBRATION_DISTANCE/estimatedDist *100
                self.cm.setKinectDistanceCal(self.kdc)
                break
            except Exception as error:
                print(error)
        self.cm.writeCache()
    #@timeIt
    def searchForQRCode(self):
        t= time()
        frame,depth = self.getFrame(),self.getDepth()
        #data,points,rectifiedImage = qrDecoder.detectAndDecode(frame)
        _,points = qrDecoder.detect(frame)
        t = mes(t,"detect")
        #self.decode(frame,points)
        #t= mes(t,"decode")
        QRCodeImg = []
        QRCodeDepthImg = np.array([])
        if points is None:
            return QRCodeImg,QRCodeDepthImg,None
        try : 
            top_left = points[0][0]
            top_right = points[0][1]
            bot_right = points[0][2]
            bot_left = points[0][3]

            y_range = [int(top_left[1]),int(bot_left[1])]
            x_range = [int(top_left[0]),int(top_right[0])]
       
            QRCodeDepthImg  = depth[y_range[0]:y_range[1],x_range[0]:x_range[1]]
            QRCodeImg = frame[ y_range[0]:y_range[1], x_range[0]:x_range[1]]
            t = mes(t,"crop")
            #cv2.imshow("QRCode",QRCodeImg)
            #print(QRCodeDepthImg)
        except Exception as error:
            print("Error finding the qr code distance",error)
        
        return QRCodeImg,QRCodeDepthImg,points
        


    def CalculateVectorDistance(self,depthImg):
        distance = 0.0 #m
        #deniz's depth calc code vvvvv
        QRCodeDepthImg = depthImg.flatten()
        try : 
            distance = int(np.average(QRCodeDepthImg))
            adjustedDistance = distance * self.kdc #@TODO change this to focal math...
        except Exception as error: 
            print("vdist error:",error)
            return 0

        print("vector",distance, adjustedDistance)
        return adjustedDistance

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
        ydistance = math.sqrt(np.abs(vectorDistance**2 - xdistance**2))
        return (xdistance,ydistance)
        #@TODO: auto calibartion with ydistance estimate and real value from a^2+b^2 = c^2.
        
        


    def update(self):
        QRCodeImg,QRCodeDepthImg,points =self.searchForQRCode()
        if points is None:
            # print("no points :(")
            return
        if DEBUG: print(QRCodeDepthImg.shape,points)
        distancePacket = self.CoordinateDistanceCalc(QRCodeDepthImg,points[0][0])
        # print(distancePacket)
        return distancePacket
    def __tiltUpdateSequence(self,dev,ctx):
        print("bodyy running")
        freenect.update_tilt_state(dev)
        state = freenect.get_tilt_state(dev)
        deg = freenect.get_tilt_degs(state)
        print(f"tilt:{deg}")
        self.tiltAngle = np.deg2rad(deg)
        self.startLoop = False
        raise freenect.Kill
    def cacheTilt(self):
        raise "Not implemented"        



if __name__ == '__main__':
    kinect = Camera()
    while True:
        print(kinect.update())




