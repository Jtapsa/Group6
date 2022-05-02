
import cv2
import numpy as np
import time
import serial
from serial import Serial



# Load the cascade data for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
#video capture object
cap = cv2.VideoCapture(0) # using computer web camera, which are connected to phone camera via Iruin
arduino = serial.Serial('/dev/cu.usbmodem1301', 115200) #Selecting used USB-Port


while 1:
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)  # mirror the image
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 6)  # detect the face
    for x, y, w, h in faces:

        # plot the center of the face --> Green dot
        dot_X = x + w // 2
        dot_Y = y + h // 2
        cv2.circle(frame, (dot_X, dot_Y), 2, (0, 255, 0), 2)
        # Rectangle for face detection
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)

        X_Start = 1920 // 2 - 10
        X_End = 1920 // 2 + 10
        Y_Start = 1080 // 2 - 10
        Y_End = 1080 // 2 + 10

        # Calculating difference for movement
        difference_X = int((X_Start + X_End)/2 - dot_X)
        difference_Y = int((Y_Start + Y_End)/2 - dot_Y)


        if difference_X < -200:
            print("Go Left")
            string = "L"
            arduino.write(string.encode('utf-8'))   #Sending commands to Arduino

        elif difference_Y < -200:
            print("Go Back")
            string = "B"
            arduino.write(string.encode('utf-8'))

        elif difference_X > 200:
            print("Go Right")
            string = "R"
            arduino.write(string.encode('utf-8'))

        elif difference_Y > 200:
            print("Go Forward")
            string = "F"
            arduino.write(string.encode('utf-8'))

        else:
            print("Stay")
            string = "S"
            arduino.write(string.encode('utf-8'))

    cv2.imshow('img', frame)

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

# Release the VideoCapture object
cap.release()
cv2.destroyAllWindows()









