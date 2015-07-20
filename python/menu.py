from random import random
from math import sin, pi

import pygame
from buffalo import utils

from buffalo.label import Label
from buffalo.button import Button

def init():

    global BACKGROUND_COLOR, R_MAX, G_MAX, B_MAX
    global BACKGROUND_COLOR_SWITCH, BACKGROUND_TIMER
    global OSCILLATION_TIME
    BACKGROUND_COLOR = R_MAX, G_MAX, B_MAX, a = (
        int(random() * 150) + 50,
        int(random() * 150) + 50,
        int(random() * 150) + 50,
        255,
        )
    BACKGROUND_COLOR_SWITCH = 0
    BACKGROUND_TIMER = 0
    OSCILLATION_TIME = 10000


    global buttons
    global labels

    buttons = set([])    
    labels = set([])

    label_version = Label(
        (5, utils.SCREEN_H - 5),
        "FPH 0.0 alpha + July 20th, 2015",
        invert_y_pos=True,
        )
    labels.add( label_version )

    button_exit = Button(
        (utils.SCREEN_W / 2, 3 * utils.SCREEN_H / 4),
        "Exit",
        x_centered=True,
        y_centered=True,
        feathering=10,
        func=exit,
        )
    buttons.add( button_exit )

    button_options = Button(
        (utils.SCREEN_W / 2, button_exit.pos[1] - 10),
        "Options",
        invert_y_pos=True,
        x_centered=True,
        feathering=10,
        )
    buttons.add( button_options )

    button_multiplayer = Button(
        (utils.SCREEN_W / 2, button_options.pos[1] - 10),
        "Multiplayer",
        invert_y_pos=True,
        x_centered=True,
        feathering=10,
        )
    buttons.add( button_multiplayer )

    button_select_character = Button(
        (utils.SCREEN_W / 2, button_multiplayer.pos[1] - 10),
        "Select Character",
        invert_y_pos=True,
        x_centered=True,
        feathering=10,
        )
    buttons.add( button_select_character )

    button_new_character = Button(
        (utils.SCREEN_W / 2, button_select_character.pos[1] - 10),
        "New Character",
        invert_y_pos=True,
        x_centered=True,
        feathering=10,
        )
    buttons.add( button_new_character )

def logic():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            utils.end = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                utils.end = True
        elif event.type == pygame.MOUSEBUTTONDOWN:
            mouse_pos = pygame.mouse.get_pos()
            for button in buttons:
                if button.get_rect().collidepoint( mouse_pos ):
                    button.set_selected(True)
        elif event.type == pygame.MOUSEBUTTONUP:
            mouse_pos = pygame.mouse.get_pos()
            for button in buttons:
                button.set_selected(False)
                if button.get_rect().collidepoint( mouse_pos ):
                    if button.func is not None:
                        button.func()

def update():

    global BACKGROUND_COLOR, BACKGROUND_TIMER, BACKGROUND_COLOR_SWITCH

    BACKGROUND_TIMER += utils.delta
    r, g, b, a = BACKGROUND_COLOR
    if BACKGROUND_COLOR_SWITCH == 0:
        r = (R_MAX + R_MAX * sin( 2 * pi * BACKGROUND_TIMER / OSCILLATION_TIME )) / 2
    elif BACKGROUND_COLOR_SWITCH == 1:
        g = (G_MAX + G_MAX * sin( 2 * pi * BACKGROUND_TIMER / OSCILLATION_TIME )) / 2
    else:
        b = (B_MAX + B_MAX * sin( 2 * pi * BACKGROUND_TIMER / OSCILLATION_TIME )) / 2
    
    if BACKGROUND_TIMER % OSCILLATION_TIME < 100:
        BACKGROUND_COLOR_SWITCH += 1
        BACKGROUND_COLOR_SWITCH %= 3
        
    BACKGROUND_COLOR = (r, g, b, a)

def render():
    utils.screen.fill( BACKGROUND_COLOR )

    for label in labels:
        label.blit( utils.screen )
    for button in buttons:
        button.blit( utils.screen )

    pygame.display.update()
    
