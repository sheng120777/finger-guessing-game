#pip install cvzone==1.4.1
#pip install mediapipe==0.8.8
#pip install pyserial
#pip install cv

import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.PoseModule import PoseDetector
from cvzone.SerialModule import SerialObject
import time

cap=cv2.VideoCapture(0)
detector=HandDetector(detectionCon=0.5,maxHands=1) 
myserial=SerialObject("COM8",9600,1)         #com port 可調 

while True:
    success,img=cap.read()
    img=detector.findHands(img)
    lmList,bbox=detector.findPosition(img)
    if lmList:
        fingers=detector.fingersUp()
        print(fingers)   
        myserial.sendData(fingers)
    img=img[:,::-1]
    cv2.imshow('img',img)
    if cv2.waitKey(1)==ord('q'):           #按Q退出
        break
cv2.destroyAllWindows() 
