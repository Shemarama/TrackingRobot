#!/usr/bin/python2

import numpy as np
import cv2
import sys
import serial
import time

face_cascade = cv2.CascadeClassifier('/home/barbie/Documents/python/opencv/facedetection/haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('/home/barbie/Documents/python/opencv/facedetection/haarcascade_eye.xml')
smile_cascade = cv2.CascadeClassifier('/home/barbie/Documents/python/opencv/facedetection/haarcascade_smile.xml')
cap = cv2.VideoCapture(0)
ser = serial.Serial('/dev/ttyUSB0',9600, timeout=1)

xcenter = 0
ycenter = 0
msg = ''

while ser.in_waiting <= 0:
    ser.write('A')
    time.sleep(0.3)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    '''
    # to detect smiles
    smiles = smile_cascade.detectMultiScale(gray, 1.9, 8)
    for (x,y,w,h) in smiles:
      cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,255),2)
    '''
    
    # to detect faces
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for key,(x,y,w,h) in enumerate(faces):
      xcenter = (x+w)/2
      ycenter = (y+h)/2
      cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
      # to detect eyes
      #roi_gray = gray[y:y+h, x:x+w]
      #roi_color = frame[y:y+h, x:x+w]
      
      #print 'Face %d = x: %d y: %d' % (key,xcenter,ycenter)

      #eyes = eye_cascade.detectMultiScale(roi_gray)
      #for ekey,(ex,ey,ew,eh) in enumerate(eyes):
      #  cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)

    # Display the resulting frame
    if ser.in_waiting > 0:
        msg = ser.readline()[:-1]
        if msg == 'x':
            ser.write(str(xcenter))
        elif msg == 'y':
            ser.write(str(ycenter))
        else:
            print 'msg = ', msg

    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        cv2.imwrite('shemdetected.jpg',frame)
        break


# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
