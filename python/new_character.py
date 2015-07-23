from random import random

import pygame

from buffalo import utils
from buffalo.label import Label
from buffalo.button import Button
from buffalo.input import Input
from buffalo.option import Option

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
    global options

    BACKGROUND_COLOR = (
        int(random() * 150) + 70,
        int(random() * 150) + 70,
        int(random() * 150) + 70,
        255
        )

    buttons = set([])
    labels = set([])
    inputs = set([])
    options = set([])

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

    label_race = Label(
        (20, label_character_name.pos[1] + label_character_name.surface.get_size()[1] + 10),
        "Race:",
        )
    labels.add( label_race )

    option_race = Option(
        (label_race.pos[0] + label_race.surface.get_size()[0] + 10, label_race.pos[1]),
        (
            "Human",
            "Wood Elf",
            "High Elf",
            "Dark Elf",
            "Dwarf",
            "Hobbit",
            "Askarian",
        )
        )
    options.add( option_race )

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
            for option in options:
                if option.get_left_rect().collidepoint( mouse_pos ):
                    option.set_left_selected(True)
                if option.get_right_rect().collidepoint( mouse_pos ):
                    option.set_right_selected(True)
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
            for option in options:
                if option.get_left_rect().collidepoint( mouse_pos ):
                    option.go_left()
                if option.get_right_rect().collidepoint( mouse_pos ):
                    option.go_right()

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
    for option in options:
        option.blit( utils.screen )    

    pygame.display.update()
