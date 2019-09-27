import random

import pygame

from aux import random_color, gameDisplay, DISPLAY_HEIGHT, DISPLAY_WIDTH


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
        self.y += self.speed

        if self.y > DISPLAY_HEIGHT:
            self.y = 0 - self.h
            self.x = random.randrange(0, DISPLAY_WIDTH)
            self.color = random_color()

        if self.y == 0 - self.h:
            self.speed += 0.05*self.speed
            self.w += 0.05*self.w
        
        return True