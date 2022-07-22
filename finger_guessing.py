#pip install cvzone==1.4.1
#pip install mediapipe==0.8.8
#pip install pyserial
#pip install cv

import cv2
from cvzone.HandTrackingModule import HandDetector
from cvzone.PoseModule import PoseDetector
from cvzone.SerialModule import SerialObject
import time
import mediapipe

cap=cv2.VideoCapture(0)
detector=HandDetector(detectionCon=0.5,maxHands=1) 
myserial=SerialObject("COM8",9600,1)

while True:
    success,img=cap.read()
    img=detector.findHands(img)
    lmList,bbox=detector.findPosition(img)
    if lmList:
        fingers=detector.fingersUp()
        #print(fingers)   
        #myserial.sendData(fingers)
        if fingers==[1,1,1,1,1]:
            print("paper")
            out=[0,0,1,1,0]      
            myserial.sendData(out)             
        if fingers==[0,1,1,0,0]:
            print("scissor")
            out=[0,0,0,0,0]
            myserial.sendData(out)
        if fingers==[0,0,0,0,0]:
            print("rock")
            out=[1,1,1,1,1]
            myserial.sendData(out)
    img=img[:,::-1]
    cv2.imshow('img',img)
    if cv2.waitKey(1)==ord('q'):
        break
cv2.destroyAllWindows() 
