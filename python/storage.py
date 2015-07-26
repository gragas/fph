import inspect
from os import listdir
from os.path import isfile, join

from race import Race
from player import Player

def init():

    global player
    player = None

    global label_player_name, label_player_race, label_player_profession
    label_player_name = None
    label_player_race = None
    label_player_profession = None

    global player_names
    player_names = []
    load_player_names()

def load_player(player_filename):

    if not player_filename[-5:] == '.save':
        print("ERROR: " + player_filename + " is not a .save file.")
        raise
    with open(join('data','saves',player_filename)) as player_file:
        for line in player_file:
            contents = line.strip().split()
            if contents[0] == 'Name:':
                name = line[line.index(contents[1]):].strip()
            elif contents[0] == 'Race:':
                race = line[line.index(contents[1]):].strip()
            elif contents[0] == 'Gender:':
                gender = line[line.index(contents[1]):].strip()
            elif contents[0] == 'Profession:':
                profession = line[line.index(contents[1]):].strip()
            elif contents[0] == 'Constitution:':
                cons = float(line[line.index(contents[1]):].strip())
            elif contents[0] == 'Endurance:':
                endu = float(line[line.index(contents[1]):].strip())
            elif contents[0] == 'Pneuma:':
                pneu = float(line[line.index(contents[1]):].strip())
            elif contents[0] == 'Resiliance:':
                resi = float(line[line.index(contents[1]):].strip())
            elif contents[0] == 'Resolution:':
                reso = float(line[line.index(contents[1]):].strip())
            elif contents[0] == 'Providence:':
                prov = float(line[line.index(contents[1]):].strip())
            elif contents[0] + " " + contents[1] == 'Cons Mult:':
                cons_mult = float(line[line.index(contents[2]):].strip())
            elif contents[0] + " " + contents[1] == 'Endu Mult:':
                endu_mult = float(line[line.index(contents[2]):].strip())
            elif contents[0] + " " + contents[1] == 'Pneu Mult:':
                pneu_mult = float(line[line.index(contents[2]):].strip())
            elif contents[0] + " " + contents[1] == 'Resi Mult:':
                resi_mult = float(line[line.index(contents[2]):].strip())
            elif contents[0] + " " + contents[1] == 'Reso Mult:':
                reso_mult = float(line[line.index(contents[2]):].strip())
            elif contents[0] + " " + contents[1] == 'Prov Mult:':
                prov_mult = float(line[line.index(contents[2]):].strip())
            elif contents[0] + " " + contents[1] == 'X Pos:':
                x = line[line.index(contents[2]):].strip()
            elif contents[0] + " " + contents[1] == 'Y Pos:':
                y = line[line.index(contents[2]):].strip()
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Base Hit Points:':
                base_hp = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Current Hit Points:':
                cur_hp = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Base Energy Points:':
                base_ep = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Current Energy Points:':
                cur_ep = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Base Pneuma Points:':
                base_pp = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Current Pneuma Points:':
                cur_pp = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Base Walk Speed:':
                base_walk_speed = float(line[line.index(contents[3]):].strip())
            elif contents[0] + " " + contents[1] + " " + contents[2] == 'Base Run Multiplier:':
                base_run_mult = float(line[line.index(contents[3]):].strip())

        global player
        player = Player(
            name,
            race,
            profession,
            cons,
            endu,
            pneu,
            resi,
            reso,
            prov,
            (x, y),
            gender=gender,
            cons_mult=cons_mult,
            endu_mult=endu_mult,
            pneu_mult=pneu_mult,
            resi_mult=resi_mult,
            reso_mult=reso_mult,
            prov_mult=prov_mult,
            base_hp=base_hp,
            base_ep=base_ep,
            base_pp=base_pp,
            running=False,
            base_walk_speed=base_walk_speed,
            base_run_mult=base_run_mult,
        )
        player.cur_hp = cur_hp
        player.cur_ep = cur_ep
        player.cur_pp = cur_pp

def load_player_names():

    # Only store the players' names, not the players themselves
    # Only one player should be loaded at any given time

    global player_names
    player_names = []

    player_filenames = [ f for f in listdir(join('data','saves')) if isfile(join('data','saves',f)) ]
    for player_filename in player_filenames:
        if not player_filename[-5:] == '.save':
            continue
        with open(join('data','saves',player_filename)) as player_file:
            for line in player_file:
                contents = line.strip().split()
                if contents[0] == 'Name:':
                    player_names.append( line[line.index(contents[1]):].strip() )

def load_races():

    def parse_mod(contents, filename):
        unparsed = contents[1].strip()
        try:
            attr_name = contents[0][:-1].lower() + "_mod"
            if attr_name not in globals():
                print("There is no attribute specified by\n")
                print(contents[0] + "\n")
                print("in file\n")
                print(join('data','races',filename))
                print("Could not convert\n")
                print(unparsed + "\n")
                print("to an integer")
                raise
            
            if unparsed[0] == '+':
                globals()[attr_name] = int(unparsed[1:])
            elif unparsed[0] == '-':
                globals()[attr_name] = int(unparsed)
            else:
                print("No sign indicated in line\n")
                print(line + "\n")
                print("in file\n")
                print(join('data','races',filename))
                raise
        
        except ValueError:
            print("Found in line\n")
            print(line + "\n")
            print("in file\n")
            print(join('data','races',filename))
            print("Could not convert\n")
            print(unparsed + "\n")
            print("to an integer")
            raise
    
    global races, race_names

    races = dict()

    # Human, Almander, Lormander, Riptide, Askarian, Eliac Elf, Ailai Elf, Dur-Mor Elf
    # Whitesmith Dwarf, Hellfire Dwarf, Deepling

    race_filenames = [ f for f in listdir(join('data','races')) if isfile(join('data','races',f)) ]
    for race_filename in race_filenames:
        if not race_filename[-5:] == '.race':
            continue
        with open(join('data','races',race_filename)) as race_file:
            global name, description, icon_filename
            global cons_mod, endu_mod, pneu_mod
            global resi_mod, reso_mod, prov_mod
            name = None
            description = None
            icon_filename = None
            cons_mod = None
            endu_mod = None
            pneu_mod = None
            resi_mod = None
            reso_mod = None
            prov_mod = None
            for line in race_file:
                contents = line.strip().split()
                if contents[0] == 'Name:':
                    name = line[line.index(contents[1]):].strip() # Everything after 'Name:'
                elif contents[0] == 'Description:':
                    description = line[line.index(contents[1]):].strip()
                elif contents[0] == 'Icon:':
                    icon_filename = line[line.index(contents[1]):].strip()
                else:
                    parse_mod(contents, race_filename)

            if cons_mod is None or \
               endu_mod is None or \
               pneu_mod is None or \
               resi_mod is None or \
               reso_mod is None or \
               prov_mod is None:
                print("Incomplete race file " + race_filename)
                raise
            
            races[name] = Race(
                name,
                description,
                icon_filename,
                cons_mod,
                endu_mod,
                pneu_mod,
                resi_mod,
                reso_mod,
                prov_mod,
            )

        race_names = sorted(list(races.keys()))
