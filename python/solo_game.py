import pygame

from buffalo import utils

import camera
from player import Player

def init():

    camera.init()

def logic():

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            utils.end = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                utils.end = True

def update():

    # A little camera movement demonstration
    speed = 0.2
    change = int(speed * utils.delta)
    
    keys = pygame.key.get_pressed()
    if keys[pygame.K_a]:
        camera.BLIT_POSITION = (camera.BLIT_POSITION[0] + change, camera.BLIT_POSITION[1])
    if keys[pygame.K_d]:
        camera.BLIT_POSITION = (camera.BLIT_POSITION[0] - change, camera.BLIT_POSITION[1])
    if keys[pygame.K_w]:
        camera.BLIT_POSITION = (camera.BLIT_POSITION[0], camera.BLIT_POSITION[1] + change)
    if keys[pygame.K_s]:
        camera.BLIT_POSITION = (camera.BLIT_POSITION[0], camera.BLIT_POSITION[1] - change)

def render():

    utils.screen.fill( (0, 0, 0, 0) )
    
    utils.screen.blit(camera.zero, camera.BLIT_POSITION)
    utils.screen.blit(camera.one, camera.BLIT_POSITION)
    # blit dynamic stuff (the player, NPCs, etc.)
    utils.screen.blit(camera.two, camera.BLIT_POSITION)

    pygame.display.update()
