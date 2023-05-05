# RPI Progress

- Initially looked for a bluetooth library to setup on the RPI with Okan

- Gave up on the bluetooth idea since we were able to checkout the Kinect from the lab. 

- Setup OpenCV and libfreenect on the RPI with Python 3.7 with Okan

- Converted our preexisting code to work with libfreenect to read distance and recognize a QR code from our RPI with Okan

- We came upon a problem where the kinect would not be able to detect and decode QR codes due to the tilt angle of the kinect and the kinect on a much lower altitude than the QR code that its trying to read.
    - We fixed this problem by employing a warp perspective algorithm that flipped the perspective on the Kinect image so that the QR code would be detectable

