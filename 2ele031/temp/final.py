import time
import random

import pygame


pygame.init()

###############################################################################
#                                 Constantes
###############################################################################
# definicao da resolucao
DISPLAY_WIDTH  = 800
DISPLAY_HEIGHT = 1000

# definicao das cores (monokai)
gray   = (39,40,34)
white  = (255,255,255)
orange = (253,151,31)
pink   = (249,38,114)
blue   = (102,217,239)
green  = (166,226,46)

# cor dos blocos
blockColors = [orange, pink, blue, green]

# definicoes gerais
gameDisplay = pygame.display.set_mode((DISPLAY_WIDTH, DISPLAY_HEIGHT))
pygame.display.set_caption("Projeto Integrado 1B!")
clock = pygame.time.Clock()

# load da imagem do carro
carImg = pygame.image.load('figs/mario.png')

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

    def update(self):
        self.x += self.dx

        if self.x > DISPLAY_WIDTH - self.w:
            self.x = DISPLAY_WIDTH - self.w
        elif self.x < 0:
            self.x = 0

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

###############################################################################
#                                 Loop
###############################################################################
def game_loop():

    # cria carro
    car = Car(x = DISPLAY_WIDTH*0.45,
              y = DISPLAY_HEIGHT*0.9, 
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
        block.update()
        block.draw()

        # atualiza carro
        car.update()
        car.draw()
    
        # verifica colisao
        check_crash(car, block)

        # atualiza placar
        score.update(block)
        score.draw()
    
        # atualiza a tela
        pygame.display.update()

        # fps
        clock.tick(60)

###############################################################################
#                                 Texto
###############################################################################
# renderiza o texto
def text_objects(text, font, color):
    textSurface = font.render(text, True, color)
    return textSurface, textSurface.get_rect()

# apresenta texto na tela
def display_message(text, color):
    largeText = pygame.font.Font('freesansbold.ttf', 115)
    
    TextSurf, TextRect = text_objects(text, largeText, color)
    TextRect.center = (DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2)

    gameDisplay.blit(TextSurf, TextRect)
    pygame.display.update()
    

###############################################################################
#                                 Auxiliares
###############################################################################
# tela inicial do jogo
def game_start():
    intro = True

    while intro:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

            if event.type == pygame.KEYUP:
                intro = False

        gameDisplay.fill(gray)
        largeText = pygame.font.Font('freesansbold.ttf',115)
        
        TextSurf, TextRect = text_objects("Press Start", largeText, white)
        TextRect.center = ((DISPLAY_WIDTH/2),(DISPLAY_HEIGHT/2))
        
        gameDisplay.blit(TextSurf, TextRect)

        pygame.display.update()
        clock.tick(15)

# pega uma cor aleatoria da lista
def random_color():
    return random.choice(blockColors)

# verifica se o houve colisao
def check_crash(car, block):
    # cruzou em y
    if car.y < block.y + block.h:
        # cruzou em x
        if car.x > block.x and car.x < block.x + block.w:
            display_message("You crashed!", white)
            
            time.sleep(2)
            
            game_start()
            game_loop()

        if car.x + car.w > block.x and car.x + car.w < block.x + block.w:
            display_message("You crashed!", white)

            time.sleep(2)

            game_start()
            game_loop()


if __name__ == "__main__":
    game_start()
    game_loop()

    pygame.quit()
    quit()