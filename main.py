import cv2
import numpy as np
import time
import serial
from serial import Serial

# Load the cascade data for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')
mouth_cascade = cv2.CascadeClassifier('./cascade_files/haarcascade_mcs_mouth.xml')
# video capture object
cap = cv2.VideoCapture(0)  # using computer web camera, which are connected to phone camera via Iruin
arduino = serial.Serial('/dev/cu.usbmodem1301', 2000000)  # Selecting used USB-Port
count = 0

while 1:
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)  # mirror the image
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.1, 6, minSize=(150, 150), flags=cv2.CASCADE_SCALE_IMAGE)  # detect the face
    for x, y, w, h in faces:

        # plot the center of the face --> Green dot
        dot_X = x + w // 2
        dot_Y = y + h // 2
        cv2.circle(frame, (dot_X, dot_Y), 2, (0, 255, 0), 2)
        # Rectangle for face detection
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 3)

        # eyes = eye_cascade.detectMultiScale(roi_gray, 1.07, 1)

        X_Start = 1920 // 2 - 10
        X_End = 1920 // 2 + 10
        Y_Start = 1080 // 2 - 10
        Y_End = 1080 // 2 + 10

        # Calculating difference for movement
        difference_X = int((X_Start + X_End) / 2 - dot_X)
        difference_Y = int((Y_Start + Y_End) / 2 - dot_Y)

        # Controlling data sending to Arduino 
        if count == 5:
            count = 0
            if abs(difference_X) - abs(difference_Y) > 0 and abs(difference_Y) > 200:

                if difference_Y > 150:
                    print("Go Back")
                    string = "B"
                    arduino.write(string.encode('utf-8'))

                elif difference_Y < - 150:
                    print("Go Forward")
                    string = "F"
                    arduino.write(string.encode('utf-8'))

            elif abs(difference_X) - abs(difference_Y) > 0 and abs(difference_X) > 100:

                if difference_X < - 250:
                    print("Go Left")
                    string = "L"
                    arduino.write(string.encode('utf-8'))  # Sending commands to Arduino

                elif difference_X > 250:
                    print("Go Right")
                    string = "R"
                    arduino.write(string.encode('utf-8'))

                elif difference_X < - 150:
                    print("Go Left little")
                    string = "A"
                    arduino.write(string.encode('utf-8'))

                elif difference_X > 150:
                    print("Go Right little")
                    string = "C"
                    arduino.write(string.encode('utf-8'))

            elif abs(difference_Y) > 150:

                if difference_Y > 150:
                    print("Go Back")
                    string = "B"
                    arduino.write(string.encode('utf-8'))

                elif difference_Y < - 150:
                    print("Go Forward")
                    string = "F"
                    arduino.write(string.encode('utf-8'))

                elif difference_Y > 80:
                    print("Go Back little")
                    string = "D"
                    arduino.write(string.encode('utf-8'))

                elif difference_Y < - 80:
                    print("Go Forward")
                    string = "E"
                    arduino.write(string.encode('utf-8'))

            else:
                print("Stay")
                string = "S"
                arduino.write(string.encode('utf-8'))

        count += 1
        string = "S"
        arduino.write(string.encode('utf-8'))

    cv2.imshow('img', frame)

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

# Release the VideoCapture object
cap.release()
cv2.destroyAllWindows()
