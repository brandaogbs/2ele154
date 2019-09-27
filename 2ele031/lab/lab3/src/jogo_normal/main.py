import time
import random

import pygame

#TODO: Documentar o código

pygame.init()

DISPLAY_WIDTH  = 800 
DISPLAY_HEIGHT = 600

gameDisplay = pygame.display.set_mode((DISPLAY_WIDTH, DISPLAY_HEIGHT))
pygame.display.set_caption("Projeto Integrador 1B")

clock = pygame.time.Clock()

gray   = (39,40,34)
orange = (253,151,31)
pink   = (249,38,114)  
blue   = (102,217,239)
green  = (166,226,46)
white  = (255,255,255)


###############################################################################
#                                 Carrinho
###############################################################################

def car_update(carX, carY, carW, carImg, dX):
    carX += dX

    if carX < 0:
        carX = 0
    elif carX > DISPLAY_WIDTH - carW:
        carX =  DISPLAY_WIDTH - carW

    gameDisplay.blit(carImg, (carX, carY))
    
    return carX


###############################################################################
#                                Bloquinho
###############################################################################
blockColors = [orange, blue, pink, green]

def block_update(blockX, blockY, blockW, blockH, blockColor, blockSpeed):

    blockY = blockY + blockSpeed

    if blockY > DISPLAY_HEIGHT:
        blockY = 0 - blockH
        blockX = random.randrange(0, DISPLAY_WIDTH)
        blockColor = random_color()
    pygame.draw.rect(gameDisplay, blockColor, [blockX, blockY, blockW, blockH])
    
    return blockX, blockY, blockColor


###############################################################################
#                                   Texto
###############################################################################
def text_objets(text, font, color):
    textSurface = font.render(text, True, color)
    return textSurface, textSurface.get_rect()

def message_display(text, color):
    largeText = pygame.font.Font("freesansbold.ttf", 115)

    TextSurf, TextRect = text_objets(text, largeText, color)
    TextRect.center = (DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2)

    gameDisplay.blit(TextSurf, TextRect)
    pygame.display.update()


###############################################################################
#                                 Auxiliares
###############################################################################
def random_color():
    return random.choice(blockColors)

#TODO: Reiniciar jogo

def check_crash(carX, carY, carW, blockX, blockY, blockW, blockH):
    if carY < blockY + blockH:
        if carX > blockX and carX < blockX + blockW:
            message_display("Você bateu!", white)
            time.sleep(2)
        if carX + carW > blockX and carX + carW < blockX + blockW:
            message_display("Você bateu!", white)
            time.sleep(2)

#TODO: Criar função de pontuação


###############################################################################
#                                 Principal
###############################################################################
def game_loop():
    carImg = pygame.image.load("figs/mario.png")
    carX = 0.45*DISPLAY_WIDTH
    carY = 0.80*DISPLAY_HEIGHT
    carW = 100
    dX = 0


    blockW = 100
    blockH = 100
    blockX = random.randrange(0, DISPLAY_WIDTH)
    blockY = 0
    blockSpeed = 5 
    blockColor = white

    score = 0

    gameExit = False

    while not gameExit:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                gameExit = True
                pygame.quit()
                quit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    dX = -5
                if event.key == pygame.K_RIGHT:
                    dX = 5

            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    dX = 0

        gameDisplay.fill(gray)

        blockX, blockY, blockColor = block_update(blockX, blockY, blockW, blockH, blockColor, blockSpeed)

        carX = car_update(carX, carY, carW, carImg, dX)

        check_crash(carX, carY, carW, blockX, blockY, blockW, blockH)

        #TODO: Atualizar a pontuação

        pygame.display.update()
        clock.tick(60)

#TODO: Criar tela de inicialização
game_loop()

pygame.quit()
quit()