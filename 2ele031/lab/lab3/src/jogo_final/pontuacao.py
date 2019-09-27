import pygame

from aux import gameDisplay, white


###############################################################################
#                                 Pontuacao
###############################################################################
class Score(object):
    
    def __init__(self, score):
        self.score = score
        self.font = pygame.font.SysFont(None, 25)
        self.text = ""

    def draw(self):
        self.text = self.font.render("Score: {}".format(self.score), True, white)
        gameDisplay.blit(self.text, (0,0))
    
    def update(self, block):
        if block.y == 0 - block.h:
            self.score += 1
        
        return True