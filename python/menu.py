from random import random

import pygame
import utils

from label import Label
from button import Button

def init():

    global BACKGROUND_COLOR
    BACKGROUND_COLOR = (
        int(random() * 150) + 50,
        int(random() * 150) + 50,
        int(random() * 150) + 50,
        255,
        )

    global label_version
    label_version = Label(
        (5, utils.SCREEN_H - 5),
        "FPH 0.0 alpha + July 15th, 2015",
        invert_y_pos=True,
        )

    global button_exit
    button_exit = Button(
        (utils.SCREEN_W / 2, 3 * utils.SCREEN_H / 4),
        "Exit",
        x_centered=True,
        y_centered=True,
        feathering=10,
        )
    
    global button_options
    button_options = Button(
        (utils.SCREEN_W / 2, button_exit.pos[1] - 10),
        "Options",
        invert_y_pos=True,
        x_centered=True,
        feathering=10,
        )

def logic():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            utils.end = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                utils.end = True

def render():
    utils.screen.fill( BACKGROUND_COLOR )

    label_version.blit( utils.screen)
    button_exit.blit( utils.screen )
    button_options.blit( utils.screen )

    pygame.display.update()
    
