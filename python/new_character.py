from random import random

import pygame

from buffalo import utils
from buffalo.label import Label
from buffalo.button import Button

import menu

def return_to_menu():
    
    utils.logic = menu.logic
    utils.update = menu.update
    utils.render = menu.render
    menu.init()

def init():

    global BACKGROUND_COLOR
    global buttons
    global labels

    BACKGROUND_COLOR = (
        int(random() * 150) + 70,
        int(random() * 150) + 70,
        int(random() * 150) + 70,
        255
        )

    buttons = set([])    
    labels = set([])

    button_back = Button(
        (5, utils.SCREEN_H - 5),
        "Back",
        invert_y_pos=True,
        feathering=10,
        func=return_to_menu,
        )
    buttons.add( button_back )

def logic():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            utils.end = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                return_to_menu()
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
    pass

def render():
    utils.screen.fill( BACKGROUND_COLOR )

    for label in labels:
        label.blit( utils.screen )
    for button in buttons:
        button.blit( utils.screen )

    pygame.display.update()
