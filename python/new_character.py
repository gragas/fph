import os.path
from random import random

import pygame

from buffalo import utils
from buffalo.label import Label
from buffalo.button import Button
from buffalo.input import Input
from buffalo.option import Option

import menu
import storage

def return_to_menu():
    
    utils.logic = menu.logic
    utils.update = menu.update
    utils.render = menu.render
    menu.init()

def create_character():

    # First create the character
    # Then go back to the main menu
    return_to_menu()

def update_race_selection():

    global race_name
    race_name = option_race.data[option_race.index]
    update_race_labels()

def update_race_labels():

    global race_name, race_description, race_icon
    global race_cons_mod, race_endu_mod, race_pneu_mod
    global race_resi_mod, race_reso_mod, race_prov_mod
    
    global label_race_description_value
    global label_race_cons_mod_value, label_race_endu_mod_value, label_race_pneu_mod_value
    global label_race_resi_mod_value, label_race_reso_mod_value, label_race_prov_mod_value

    if not storage.races:
        race_description = "None"
        race_icon = utils.empty_surface( (0, 0) )
        race_cons_mod = "None"
        race_endu_mod = "None"
        race_pneu_mod = "None"
        race_resi_mod = "None"
        race_reso_mod = "None"
        race_prov_mod = "None"
    else:
        race_description = storage.races[race_name].description
        try:
            race_icon = pygame.image.load(
                os.path.join(
                    'data','races','icons',storage.races[race_name].icon_filename
                )
            ).convert_alpha()
        except:
            race_icon = utils.empty_surface( (0, 0) )
        race_cons_mod = str(storage.races[race_name].cons_mod)
        race_endu_mod = str(storage.races[race_name].endu_mod)
        race_pneu_mod = str(storage.races[race_name].pneu_mod)
        race_resi_mod = str(storage.races[race_name].resi_mod)
        race_reso_mod = str(storage.races[race_name].reso_mod)
        race_prov_mod = str(storage.races[race_name].prov_mod)
        for n in ("cons", "endu", "pneu", "resi", "reso", "prov",):
            if int(globals()["race_" + n + "_mod"]) > 0:
                globals()["race_" + n + "_mod"] = "+" + globals()["race_" + n + "_mod"]

    label_race_description_value.text = race_description
    label_race_description_value.render()
    label_race_cons_mod_value.text = race_cons_mod
    label_race_cons_mod_value.render()
    label_race_endu_mod_value.text = race_endu_mod
    label_race_endu_mod_value.render()
    label_race_pneu_mod_value.text = race_pneu_mod
    label_race_pneu_mod_value.render()
    label_race_resi_mod_value.text = race_resi_mod
    label_race_resi_mod_value.render()
    label_race_reso_mod_value.text = race_reso_mod
    label_race_reso_mod_value.render()
    label_race_prov_mod_value.text = race_prov_mod
    label_race_prov_mod_value.render()

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

    button_create = Button(
        (button_back.pos[0] + button_back.size[0] + 10, utils.SCREEN_H - 20),
        "Create",
        invert_y_pos=True,
        func=create_character,
        )
    buttons.add( button_create )

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

    global race_name, race_description, race_icon
    global race_cons_mod, race_endu_mod, race_pneu_mod
    global race_resi_mod, race_reso_mod, race_prov_mod
    
    global label_race_description_value
    global label_race_cons_mod_value, label_race_endu_mod_value, label_race_pneu_mod_value
    global label_race_resi_mod_value, label_race_reso_mod_value, label_race_prov_mod_value

    global option_race

    storage.load_races()

    if storage.races:
        race_name = storage.races[storage.race_names[0]].name
    
    option_race = Option(
        (label_race.pos[0] + label_race.surface.get_size()[0] + 10, label_race.pos[1]),
        storage.race_names,
        rfunc=update_race_selection,
        lfunc=update_race_selection,
    )
    options.add( option_race )

    label_race_description = Label(
        (
            20,
            label_race.pos[1] + label_race.surface.get_size()[1] + 10 + \
            64 + 10,
        ),
        "Description:",
    )
    labels.add( label_race_description )

    label_race_description_value = Label(
        (
            label_race_description.pos[0] + label_race_description.surface.get_size()[0] + 10,
            label_race_description.pos[1]
        ),
        "None",
    )
    labels.add( label_race_description_value )

    label_race_cons_mod = Label(
        (
            20,
            label_race_description_value.pos[1] + \
            label_race_description_value.surface.get_size()[1] + 10
        ),
        "Constitution Mod:",
    )
    labels.add( label_race_cons_mod )

    label_race_cons_mod_value = Label(
        (
            label_race_cons_mod.pos[0] + label_race_cons_mod.surface.get_size()[0] + 10,
            label_race_cons_mod.pos[1]
        ),
        "None",
    )
    labels.add( label_race_cons_mod_value )

    label_race_endu_mod = Label(
        (
            20,
            label_race_cons_mod.pos[1] + \
            label_race_cons_mod.surface.get_size()[1] + 10
        ),
        "Endurance Mod:",
    )
    labels.add( label_race_endu_mod )

    label_race_endu_mod_value = Label(
        (
            label_race_cons_mod_value.pos[0] + label_race_cons_mod_value.surface.get_size()[0],
            label_race_endu_mod.pos[1]
        ),
        "None",
        invert_x_pos=True,
    )
    labels.add( label_race_endu_mod_value )

    label_race_pneu_mod = Label(
        (
            20,
            label_race_endu_mod.pos[1] + \
            label_race_endu_mod.surface.get_size()[1] + 10
        ),
        "Pneuma Mod:",
    )
    labels.add( label_race_pneu_mod )

    label_race_pneu_mod_value = Label(
        (
            label_race_cons_mod_value.pos[0] + label_race_cons_mod_value.surface.get_size()[0],
            label_race_pneu_mod.pos[1]
        ),
        "None",
        invert_x_pos=True,
    )
    labels.add( label_race_pneu_mod_value )

    label_race_resi_mod = Label(
        (
            20,
            label_race_pneu_mod.pos[1] + \
            label_race_pneu_mod.surface.get_size()[1] + 10
        ),
        "Resiliance Mod:",
    )
    labels.add( label_race_resi_mod )

    label_race_resi_mod_value = Label(
        (
            label_race_cons_mod_value.pos[0] + label_race_cons_mod_value.surface.get_size()[0],
            label_race_resi_mod.pos[1]
        ),
        "None",
        invert_x_pos=True,
    )
    labels.add( label_race_resi_mod_value )

    label_race_reso_mod = Label(
        (
            20,
            label_race_resi_mod.pos[1] + \
            label_race_resi_mod.surface.get_size()[1] + 10
        ),
        "Resolution Mod:",
    )
    labels.add( label_race_reso_mod )

    label_race_reso_mod_value = Label(
        (
            label_race_cons_mod_value.pos[0] + label_race_cons_mod_value.surface.get_size()[0],
            label_race_reso_mod.pos[1]
        ),
        "None",
        invert_x_pos=True,
    )
    labels.add( label_race_reso_mod_value )

    label_race_prov_mod = Label(
        (
            20,
            label_race_reso_mod.pos[1] + \
            label_race_reso_mod.surface.get_size()[1] + 10
        ),
        "Providence Mod:",
    )
    labels.add( label_race_prov_mod )

    label_race_prov_mod_value = Label(
        (
            label_race_cons_mod_value.pos[0] + label_race_cons_mod_value.surface.get_size()[0],
            label_race_prov_mod.pos[1]
        ),
        "None",
        invert_x_pos=True,
    )
    labels.add( label_race_prov_mod_value )

    update_race_labels()

    label_profession = Label(
        (20, label_race_prov_mod.pos[1] + label_race_prov_mod.surface.get_size()[1] + 10),
        "Profession:",
    )
    labels.add( label_profession )

    option_profession = Option(
        (
            label_profession.pos[0] + label_profession.surface.get_size()[0] + 10,
            label_profession.pos[1]
        ),
        (
            "Alchemist",
            "Geologist",
            "Ethnobotanist",
            "Diviner",
            "Shaman",
            "Hunter",
            "Gatherer",
            "Merchant",
            "Mercenary",
            "Enchanter",
            "Rider",
            "Guard",
            "Mage",
            "Environmentalist",
            "Eschatologist",
            "Biologist",
            "Theif",
            "Beggar",
            "Smith",
            "Fletcher",
            "Leatherworker",
            "Monk",
            "Mathematician",
        )
        )
    options.add( option_profession )

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
    utils.screen.blit(
        race_icon,
        (
            20,
            option_race.pos[1] + option_race.size[1] + 10
        )
    )

    pygame.display.update()
