#!/usr/bin/python2

# 480,640 = h,w

import numpy as np
import cv2
import sys
import serial
import time

# load the haarcascades
face_cascade = cv2.CascadeClassifier('/home/barbie/Documents/python/opencv/facedetection/haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('/home/barbie/Documents/python/opencv/facedetection/haarcascade_eye.xml')

# get camera
cap = cv2.VideoCapture(0)

# open Serial Port on USB0 with 57600 Baud Rate
ser = serial.Serial('/dev/ttyUSB0',57600, timeout=1)

# for center of face
xcenter = 0
ycenter = 0

# check if arduino is ready
while ser.in_waiting <= 0:
    ser.write('A')
    time.sleep(0.3)

# arduino is ready at this point

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # to detect faces
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    for key,(x,y,w,h) in enumerate(faces):
      xcenter = (x+(x+w))/2
      ycenter = (y+(y+h))/2
      cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
      '''
      # to detect eyes
      roi_gray = gray[y:y+h, x:x+w]
      roi_color = frame[y:y+h, x:x+w]

      eyes = eye_cascade.detectMultiScale(roi_gray)
      for ekey,(ex,ey,ew,eh) in enumerate(eyes):
        cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
      '''

    # if arduino sent a message
    if ser.in_waiting > 0:
        print 'msg = ', ser.readline().strip()
        ser.write(str(xcenter) + ' ' + str(ycenter))

    # Display the resulting frame
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
