from random import random

import pygame

from buffalo import utils
from buffalo.label import Label
from buffalo.button import Button
from buffalo.input import Input

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
    global inputs

    BACKGROUND_COLOR = (
        int(random() * 150) + 70,
        int(random() * 150) + 70,
        int(random() * 150) + 70,
        255
        )

    buttons = set([])
    labels = set([])
    inputs = set([])

    button_back = Button(
        (20, utils.SCREEN_H - 20),
        "Back",
        invert_y_pos=True,
        func=return_to_menu,
        )
    buttons.add( button_back )

    global value_character_name
    value_character_name = "Tom"

    def set_character_name():
        global value_character_name
        value_character_name = input_character_name.label.text

    label_character_name = Label(
        (20, 20),
        "Character Name:",
        )
    labels.add( label_character_name )

    input_character_name = Input(
        ( 
            label_character_name.pos[0] + \
                label_character_name.surface.get_size()[0] + 10,
            label_character_name.pos[1] 
            ),
        value_character_name,
        func=set_character_name,
        )
    inputs.add( input_character_name )

def logic():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            utils.end = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                return_to_menu()
            else:
                for inpt in inputs:
                    if inpt.selected:
                        inpt.process_char( event.key )
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
            for inpt in inputs:
                if inpt.get_rect().collidepoint( mouse_pos ):
                    inpt.select()
                else:
                    inpt.deselect()

def update():
    pass

def render():
    utils.screen.fill( BACKGROUND_COLOR )

    for label in labels:
        label.blit( utils.screen )
    for inpt in inputs:
        inpt.blit( utils.screen )
    for button in buttons:
        button.blit( utils.screen )

    pygame.display.update()
