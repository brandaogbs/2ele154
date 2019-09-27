import time

import pygame

from aux import gameDisplay, DISPLAY_WIDTH, DISPLAY_HEIGHT, display_message, white


###############################################################################
#                                 Carro
###############################################################################
class Car(object):
    def __init__(self, x, y, width, img):
        self.x = x
        self.y = y
        self.w = width
        self.img = img
        self.dx = 0

    def draw(self):
        gameDisplay.blit(self.img, (self.x, self.y))

    def update(self, enemy):
        self.x += self.dx

        if self.x > DISPLAY_WIDTH - self.w:
            self.x = DISPLAY_WIDTH - self.w
        elif self.x < 0:
            self.x = 0

        if self.is_crashed(enemy):
            display_message("You crashed!", white)

            time.sleep(2)
            return False
        
        return True
            # game_start()

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
