import numpy as np
import cv2
import freenect

def rotateImage(input, alpha, beta, gamma, dx, dy, dz, f):
    alpha = (alpha ) * np.pi / 180.
    beta = (beta ) * np.pi / 180.
    gamma = (gamma ) * np.pi / 180.
    # get width and height for ease of use in matrices
    w = input.shape[1]
    h = input.shape[0]
    # Projection 2D -> 3D matrix
    A1 = np.array([[1, 0, -w/2],
    [0, 1, -h/2],
    [0, 0, 0],
    [0, 0, 1]], dtype=np.float64)
    # Rotation matrices around the X, Y, and Z axis
    RX = np.array([[1, 0, 0, 0],
    [0, np.cos(alpha), -np.sin(alpha), 0],
    [0, np.sin(alpha), np.cos(alpha), 0],
    [0, 0, 0, 1]], dtype=np.float64)
    RY = np.array([[np.cos(beta), 0, -np.sin(beta), 0],
    [0, 1, 0, 0],
    [np.sin(beta), 0, np.cos(beta), 0],
    [0, 0, 0, 1]], dtype=np.float64)
    RZ = np.array([[np.cos(gamma), -np.sin(gamma), 0, 0],
    [np.sin(gamma), np.cos(gamma), 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1]], dtype=np.float64)
    # Composed rotation matrix with (RX, RY, RZ)
    R = np.matmul(np.matmul(RX, RY), RZ)
    # Translation matrix
    T = np.array([[1, 0, 0, dx],
    [0, 1, 0, dy],
    [0, 0, 1, dz],
    [0, 0, 0, 1]], dtype=np.float64)
    # 3D -> 2D matrix
    A2 = np.array([[f, 0, w/2, 0],
    [0, f, h/2, 0],
    [0, 0, 1, 0]], dtype=np.float64)
    # Final transformation matrix
    trans = np.matmul(A2, np.matmul(T, np.matmul(R, A1)))
    # Apply matrix transformation
    output = cv2.warpPerspective(input, trans, (w,h), flags=cv2.INTER_LANCZOS4)
    return output,trans
def unrotate(image,trans):
    w = image.shape[1]
    h = image.shape[0]
    inv = np.linalg.inv(trans)
    # Apply matrix transformation
    print(inv)
    output = cv2.warpPerspective(image, inv, (w,h//2), flags=cv2.INTER_LANCZOS4)
    return output,inv
def getFrame():
    array,_ = freenect.sync_get_video()
    array = cv2.cvtColor(array,cv2.COLOR_RGB2GRAY)
    #array = cv2.resize(array,(RESIZE,RESIZE),interpolation=cv2.INTER_AREA)
    #array = cv2.GaussianBlur(array,KERNEL_SIZE,X_STD)
    return array
#@timeIt
def getDepth():
    t= time()
    array,_ = freenect.sync_get_depth() 
    t= mes(t,"get s")
    array = array / 10.0 #to cm
    t= mes(t,"dvd")
    #array = cv2.resize(array,(RESIZE,RESIZE),interpolation=cv2.INTER_AREA)
    array = cv2.GaussianBlur(array,KERNEL_SIZE,X_STD)
    t= mes(t,"blur")
    return array
def body(dev,ctx):
    print("bodyy running")
    freenect.update_tilt_state(dev)
    state = freenect.get_tilt_state(dev)
    deg = freenect.get_tilt_degs(state)
    print(f"tilt:{deg}")
    tiltAngle = np.deg2rad(deg)
    startLoop = False
    raise freenect.Kill

# img = getFrame()
# cv2.imwrite("bruh.png",img)
# freenect.runloop(body=body)

# img = cv2.imread("bruh.png")
# quit()
while True:
    img = getFrame()
    # print(img.shape)
    h,w = img.shape
    img = img[0:h//2,:]
    angle = 24
    rotated,rot = rotateImage(img,angle, 0, 0, 0, 0,200,200)
    # print(img.shape,rotated.shape)
    (thresh, blackAndWhiteImage) = cv2.threshold(rotated, 180, 255, cv2.THRESH_BINARY)
    cv2.imwrite("untilt.png",rotated)
    cv2.imwrite("bw.png",blackAndWhiteImage)

    qrDecoder = cv2.QRCodeDetector()
    _,points = qrDecoder.detect(blackAndWhiteImage)
    # print(f"\033[31m bw:{points!=None} \033[0m")
    _,points = qrDecoder.detect(img)
    print(f"\033[32m og:{points!=None} \033[0m")
    _,points = qrDecoder.detect(rotated)
    print(f"\033[35m rot:{points!=None} \033[0m")