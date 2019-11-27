import serial
import time
import random
import math
import pygame

pygame.init()

DISPLAY_WIDTH  = 800
DISPLAY_HEIGHT = 600

gameDisplay = pygame.display.set_mode((DISPLAY_WIDTH, DISPLAY_HEIGHT))
pygame.display.set_caption("Projeto Sist. Embarcados")

clock = pygame.time.Clock()

gray   = (39,40,34)
orange = (253,151,31)
pink   = (249,38,114)
blue   = (102,217,239)
green  = (166,226,46)
white  = (255,255,255)

ser = serial.Serial('/dev/ttyUSB0')
ser.flushInput()

def get_accel():
    ser_bytes = ser.readline().decode('utf-8')
    accel = ser_bytes.strip().split()
        
    accel_data = {  'ax' : int(accel[0].replace("\x00", ""))*0.006,
                    'ay' : int(accel[1].replace("\x00", ""))*0.006,
                    'az' : int(accel[2].replace("\x00", ""))*0.006}

    ax = accel_data['ax']
    ay = accel_data['ay']
    az = accel_data['az']

    xAngle = math.atan( ax / (math.sqrt(ay**2 + az**2)))
    yAngle = math.atan( ay / (math.sqrt(ax**2 + az**2)))
    zAngle = math.atan( math.sqrt(ax**2 + ay**2) / az)

    xAngle *= -180.00
    yAngle *= 180.00
    zAngle *= 180.00
    xAngle /= 3.141592 
    yAngle /= 3.141592 
    zAngle /= 3.141592

    accel_data = {  'ax' : xAngle,
                    'ay' : yAngle,
                    'az' : zAngle}
                    
    print("x:{:10.2f}\ny:{:10.2f}\nz:{:10.2f}\n".format(accel_data['ax'],accel_data['ay'],accel_data['az']) )
    return accel_data


###############################################################################
#                                 Blocos
###############################################################################
class Block(object):

    def __init__(self, x, y, width, height, color, speed):
        self.x = x
        self.y = y
        self.w = width
        self.h = height
        self.color = color
        self.speed = speed

    def draw(self):
        pygame.draw.rect(gameDisplay, self.color, [self.x, self.y, self.w, self.h])

    def update(self):
        accel_data = get_accel()

        self.y += accel_data['ay']/10
        self.x += accel_data['ax']/10


        if self.x > DISPLAY_WIDTH:
            self.x = DISPLAY_WIDTH

        if self.x < 0:
            self.x = 0

        if self.y > DISPLAY_HEIGHT:
            self.y = DISPLAY_HEIGHT

        if self.y < 0:
            self.y = 0



def game_loop():
    block = Block(DISPLAY_WIDTH//2, DISPLAY_HEIGHT//2, 10, 10, green, 1)

    while True:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    pygame.quit()
                    quit()



        gameDisplay.fill(gray)

        block.update()
        block.draw()

        pygame.display.update()
        clock.tick(60)

game_loop()

pygame.quit()
quit()