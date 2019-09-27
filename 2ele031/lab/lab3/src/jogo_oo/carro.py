import time

import pygame

from aux import gameDisplay, DISPLAY_WIDTH, DISPLAY_HEIGHT, display_message, white


###############################################################################
#                                 Carro
###############################################################################
class Car(object):
    def __init__(self, x, y, width, img):
        pass
    
    def draw(self):
        pass

    def update(self, enemy):        
        return True

    def is_crashed(self, enemy):
        isCrashed = False

        # cruzou em y
        if self.y < enemy.y + enemy.h:
            # cruzou em x
            if self.x > enemy.x and self.x < enemy.x + enemy.w:
                isCrashed = True

            if self.x + self.w > enemy.x and self.x + self.w < enemy.x + enemy.w:
                isCrashed = True

        return isCrashed
