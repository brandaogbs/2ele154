import time
import random

import pygame

from aux import *
from carro import Car
from bloco import Block
from pontuacao import Score


pygame.init()

###############################################################################
#                           Tela Inicial
###############################################################################
def game_start():
    intro = True

    while intro:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYUP:
                if event.key == pygame.K_RETURN:
                    intro = False
                    game_loop()


        gameDisplay.fill(gray)
        largeText = pygame.font.Font('freesansbold.ttf',115)
        
        TextSurf, TextRect = text_objects("Press Start", largeText, white)
        TextRect.center = ((DISPLAY_WIDTH/2),(DISPLAY_HEIGHT/2))
        
        gameDisplay.blit(TextSurf, TextRect)

        pygame.display.update()
        clock.tick(15)


###############################################################################
#                                 Loop
###############################################################################
def game_loop():

    # cria carro
    car = Car(x = DISPLAY_WIDTH*0.45,
              y = DISPLAY_HEIGHT*0.8, 
              width = 100, 
              img = carImg)

    # cria bloco
    block = Block(x = random.randrange(0, DISPLAY_WIDTH), 
                  y = -DISPLAY_HEIGHT, 
                  width = 100, 
                  height = 100, 
                  color = random_color(), 
                  speed = 10)                  
    
    # cria ponto
    score = Score(score=0)

    while True:
        # background
        gameDisplay.fill(gray)

        # tratamento dos eventos    
        for event in pygame.event.get():
            # quit
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()                
            
            # botao foi pressionado
            if event.type == pygame.KEYDOWN:
                # esquerda
                if event.key == pygame.K_LEFT:
                    car.dx = -10
                # direita
                elif event.key == pygame.K_RIGHT:
                    car.dx = 10

            # botao foi solto
            if event.type == pygame.KEYUP:
                # esquerda ou direia
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    car.dx = 0

        # atualiza bloco
        if block.update():
            block.draw()
        else:
            game_start()

        # atualiza carro
        if car.update(block):
            car.draw()
        else:
            game_start()

        # atualiza placar
        if score.update(block):
            score.draw()
        else:
            game_start()
    
        # atualiza a tela
        pygame.display.update()

        clock.tick(60)


if __name__ == "__main__":
    game_start()

    pygame.quit()
    quit()