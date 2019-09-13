import time
import random

import pygame


# inicia o pygame
pygame.init()

DISPLAY_WIDTH  = 800 
DISPLAY_HEIGHT = 600

# cria uma tela 800x600
gameDisplay = pygame.display.set_mode((DISPLAY_WIDTH, DISPLAY_HEIGHT))
pygame.display.set_caption("Projeto Integrador 1B")

# clock do jogo
clock = pygame.time.Clock()

# cores
gray   = (39,40,34)
orange = (253,151,31)
pink   = (249,38,114)  
blue   = (102,217,239)
green  = (166,226,46)
white  = (255,255,255)


###############################################################################
#                                 Carrinho
###############################################################################
# imagem do carrinho
carImg = pygame.image.load("figs/mario.png")

# tamanho do carro
carW = 100

# atualiza posicao e desenha o carrinho
def car_update(carX, carY, dX):
    # atualiza posição do carro
    carX += dX

    # verifica as bordas
    if carX < 0:
        carX = 0
    elif carX > DISPLAY_WIDTH - carW:
        carX =  DISPLAY_WIDTH - carW

    # desenha o carro no mapa
    gameDisplay.blit(carImg, (carX, carY))
    
    return carX


###############################################################################
#                                Bloquinho
###############################################################################
# cores dos blocos
blockColors = [orange, blue, pink, green]

# atualiza posição e desenha o bloquinho
def block_update(blockX, blockY, blockW, blockH, blockColor, blockSpeed):

    # atualiza posição do bloquinho
    blockY = blockY + blockSpeed

    # verifica se passou do chão
    if blockY > DISPLAY_HEIGHT:
        # volta bloco para o topos
        blockY = 0 - blockH
        # escolhe uma posicao aleatoria em x 
        blockX = random.randrange(0, DISPLAY_WIDTH)
        # escolhe uma cor aleatoria
        blockColor = random_color()

    # desenha bloquinho
    pygame.draw.rect(gameDisplay, blockColor, [blockX, blockY, blockW, blockH])
    
    return blockX, blockY, blockColor

def check_crash(carX, carY, carW, blockX, blockY, blockW, blockH):
    # verifica se cruzou em y
    if carY < blockY + blockH:
        # verificar se cruzou em x
        if carX > blockX and carX < blockX + blockW:
            message_display("Você bateu!", white)
        if carX + carW > blockX and carX + carW < blockX + blockW:
            message_display("Você bateu!", white)
            

###############################################################################
#                                   Texto
###############################################################################
# renderiza texto
def text_objets(text, font, color):
    textSurface = font.render(text, True, color)
    return textSurface, textSurface.get_rect()

# desenha texto na tela
def message_display(text, color):
    largeText = pygame.font.Font("freesansbold.ttf", 115)

    TextSurf, TextRect = text_objets(text, largeText, color)
    TextRect.center = (DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2)

    gameDisplay.blit(TextSurf, TextRect)
    pygame.display.update()

    time.sleep(2)
    game_loop()



###############################################################################
#                                 Auxiliares
###############################################################################
# retorna uma cor aleatoria
def random_color():
    return random.choice(blockColors)

# atualiza os pontos, a velocidade e o tamanho do bloco
def score_update(score, blockY, blockH, blockW, blockSpeed):
    font = pygame.font.SysFont(None, 25)
    text = font.render("Score: {}".format(score), True, white)

    if blockY == 0 - blockH:
        score += 1
        blockSpeed += 0.05*blockSpeed
        blockW += 0.05*blockW

    gameDisplay.blit(text, (0,0))
    return score, blockSpeed, blockW


# loop principal do jogo
def game_loop():
    # posicao inicial do carrinho
    carX = 0.45*DISPLAY_WIDTH
    carY = 0.80*DISPLAY_HEIGHT

    # deslocamento relativo do carrinho 
    dX = 0
    score = 0

    # definicioes dos blocos
    blockW = 100
    blockH = 100
    blockX = random.randrange(0, DISPLAY_WIDTH)
    blockY = 0
    blockSpeed = 5 
    blockColor = white

    # controla o fechamento do jogo
    gameExit = False

    # loop do jogo
    while not gameExit:
        
        # detecta os eventos
        for event in pygame.event.get():
            # evento de fechar
            if event.type == pygame.QUIT:
                gameExit = True
                pygame.quit()
                quit()

            # evento dos direcionais (pressionado)
            if event.type == pygame.KEYDOWN:
                # direcional para a esquerda
                if event.key == pygame.K_LEFT:
                    dX = -5
                # direcional para a direita
                if event.key == pygame.K_RIGHT:
                    dX = 5

            # evento dos direcionais (soltou)
            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    dX = 0

        # pinta a tela
        gameDisplay.fill(gray)

        # atualiza posição do carrinho
        blockX, blockY, blockColor = block_update(blockX, blockY, blockW, blockH, blockColor, blockSpeed)

        # atualiza posição do carrinho
        carX = car_update(carX, carY, dX)

        # verifica se bateu
        check_crash(carX, carY, carW, blockX, blockY, blockW, blockH)

        # atualiza score
        score, blockSpeed, blockW = score_update(score, blockY, blockH, blockW, blockSpeed)

        # atualiza display
        pygame.display.update()

        # fixa fps da tela
        clock.tick(60)

# loop
game_loop()

# fecha o pygame
pygame.quit()
quit()