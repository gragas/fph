import inspect
from os import listdir
from os.path import isfile, join

from race import Race

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
