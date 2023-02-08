import cv2
import face_recognition
import numpy as np
import RPi.GPIO as GPIO
from smbus import SMBus
 
addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1

#tolrância entre distncias atuais das faces em relação ao centro da tela
janela_erro = 18
def servoIncrementX(x, activate):
    if not activate:
        bus.write_byte(addr, 0x5)
        return
    #diferença entre a distancia atual e o centro da tela, no eixo x
    delthaX = x-480/2
    #intervalo de subtração de coordenadas em que não é necessário se mover                                   
    janela = 0
    if delthaX>janela:
        #virar servo à esquerda
        bus.write_byte(addr, 0x1)
    elif delthaX<janela:
        #virar servo à direita
        bus.write_byte(addr, 0x2)
def servoIncrementY(y, activate):
    if not activate:
        bus.write_byte(addr, 0x5)
        return
    #diferença entre a distancia atual e o centro da tela, no intervalo y
    delthaY = y-320/2
    #intervalo de subtração de coordenadas em que não é necessário se mover                                   
    janela = 0
    if delthaY>janela:
        #virar servo à esquerda
        bus.write_byte(addr, 0x4)
    elif delthaY<-janela:
        #virar servo à direita
        bus.write_byte(addr, 0x3)
def main():
    # Load the cascade
    face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

    # To capture video from webcam. 
    cap = cv2.VideoCapture(0)
    # Lower resolution
    #width
    cap.set(3, 480)
    #height
    cap.set(4, 320)

    while True:
        # Read the frame
        _, img = cap.read()
        #invert camera
        frameInvertido = cv2.flip(img, -1)
        # Convert to grayscale
        gray = cv2.cvtColor(frameInvertido, cv2.COLOR_BGR2GRAY)
        # Detect the faces
        faces = face_cascade.detectMultiScale(gray, 1.1, 4)
        # Draw the rectangle around each face
        for (x, y, w, h) in faces:
            cv2.rectangle(frameInvertido, (x, y), (x+w, y+h), (255, 0, 0), 2)
            print(f'Distance from center: X: {x-240};Y: {y-320/2}')
            #Caso valor acima da "janela" de erro, acionar os motores para correção
            if np.abs(x-240) > janela_erro or np.abs(y-320/2) > janela_erro:
                #aciona o servo no arduino via comunicação i2C
                servoIncrementX(x, True)
                servoIncrementY(y, True)
            else:
                #Do not activate the servo motors
                servoIncrementX(_, False)
                servoIncrementY(_, False)
            break
        # Display
        cv2.imshow('video', frameInvertido)
        # Hit 'q' on the keyboard to quit!
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    # Release the VideoCapture object
    cap.release()
    GPIO.cleanup()
main()