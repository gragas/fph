from random import random

import pygame

from buffalo import utils
from buffalo.label import Label
from buffalo.button import Button
from buffalo.option import Option

import storage
import menu

def back_to_menu():

    menu.gen_player_labels()

    utils.logic = menu.logic
    utils.update = menu.update
    utils.render = menu.render
    menu.init()

def update_character_labels():

    if storage.label_player_profession is None:
        storage.label_player_profession = Label(
            (
                option_characters.pos[0] + 32 + 10,
                option_characters.pos[1] - 10,
            ),
            storage.player.profession,
            invert_y_pos=True,
        )
    if storage.label_player_race is None:
        storage.label_player_race = Label(
            (
                storage.label_player_profession.pos[0],
                storage.label_player_profession.pos[1] - 10,
            ),
            storage.player.race,
            invert_y_pos=True,
        )
    if storage.label_player_name is None:
        storage.label_player_name = Label(
            (
                storage.label_player_race.pos[0],
                storage.label_player_race.pos[1] - 10,
            ),
            storage.player.name,
            invert_y_pos=True,
        )
        
    storage.label_player_profession.text = storage.player.profession
    storage.label_player_profession.render()
    storage.label_player_race.text = storage.player.race
    storage.label_player_race.render()

def update_character_selection():

    global character_name
    character_name = option_characters.data[option_characters.index]
    storage.load_player( character_name + '.save' )
    update_character_labels()

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
        func=back_to_menu,
    )
    buttons.add( button_back )

    storage.load_player_names()
    
    global option_characters
    option_characters = Option(
        utils.SCREEN_M,
        storage.player_names,
        x_centered=True,
        y_centered=True,
        rfunc=update_character_selection,
        lfunc=update_character_selection,
    )
    options.add( option_characters )
    update_character_selection()

def logic():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            utils.end = True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                back_to_menu()
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
            for option in options:
                if option.get_left_rect().collidepoint( mouse_pos ):
                    option.go_left()
                if option.get_right_rect().collidepoint( mouse_pos ):
                    option.go_right()

def update():

    pass

def render():

    utils.screen.fill( BACKGROUND_COLOR )
    
    for button in buttons:
        button.blit( utils.screen )
    for label in labels:
        label.blit( utils.screen )
    for option in options:
        option.blit( utils.screen )
    for inpt in inputs:
        inpt.blit( utils.screen )

    storage.player.blit_at(
        utils.screen,
        (
            option_characters.pos[0],
            option_characters.pos[1] - 10 - 64,
        ),
    )
    storage.label_player_profession.blit( utils.screen )
    storage.label_player_race.blit( utils.screen )

    pygame.display.update()
