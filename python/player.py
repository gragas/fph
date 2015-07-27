import os.path

import pygame

from buffalo import utils
from character import Character

class Player(Character):
    def __init__(
            self,
            name,
            race,
            profession,
            cons,
            endu,
            pneu,
            resi,
            reso,
            prov,
            pos,
            gender='male', # Create this option in the new character screen
            cons_mult=1.0,
            endu_mult=1.0,
            pneu_mult=1.0,
            resi_mult=0.6,
            reso_mult=0.6,
            prov_mult=0.6,
            base_hp=10,
            base_ep=10,
            base_pp=10,
            running=False,
            base_walk_speed=0.004,
            base_run_mult=1.9,
            ):
        super(Player, self).__init__(
            name,
            race,
            profession,
            cons,
            endu,
            pneu,
            resi,
            reso,
            prov,
            cons_mult,
            endu_mult,
            pneu_mult,
            resi_mult,
            reso_mult,
            prov_mult,
            pos,
            running,
            gender,
            base_hp,
            base_ep,
            base_pp,
            base_walk_speed,
            base_run_mult,
        )
        self.load_race_models()
        self.surface = utils.empty_surface( (32, 64) )
        self.surface.blit( self.down0, (0, 0) )
        self.walk_time = utils.delta
        self.blit_pos = utils.SCREEN_W / 2, utils.SCREEN_H / 2
        self.immobile = False
        self.calculate_speeds()
        self.update_point_bars()

    def load_race_models(self):
        try:
            self.down0 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'down0.png'
                )
            )
            self.right0 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'right0.png'
                )
            )
            self.right1 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'right1.png'
                )
            )
            self.right2 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'right2.png'
                )
            )
            self.right3 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'right3.png'
                )
            )
            self.left0 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'left0.png'
                )
            )
            self.left1 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'left1.png'
                )
            )
            self.left2 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'left2.png'
                )
            )
            self.left3 = pygame.image.load(
                os.path.join(
                    'data','fph','race_models',self.gender,self.race,'left3.png'
                )
            )
        except:
            print(
                "Could not load " + self.race + " race model."
            )
            raise

    def calculate_speeds(self):
        self.walk_speed = self.base_walk_speed # + bonuses
        self.run_mult = self.base_run_mult # + bonuses

    def update_point_bars(self):
        self.hp_rect = utils.empty_surface(
            (
                int(100.0 * self.cur_hp / self.max_hp),
                15,
            )
        )
        self.hp_rect.fill( (255, 0, 0, 255) )
        self.ep_rect = utils.empty_surface(
            (
                int(100.0 * self.cur_ep / self.max_ep),
                15,
            )
        )
        self.ep_rect.fill( (255, 255, 0, 255) )
        self.pp_rect = utils.empty_surface(
            (
                int(100.0 * self.cur_pp / self.max_pp),
                15,
            )
        )
        self.pp_rect.fill( (0, 0, 255, 255) )


    def save(self):
        with open(os.path.join('data','saves', self.name + '.save'), 'w') as save_file:
            save_file.write('Name: ' + self.name + '\n')
            save_file.write('Race: ' + self.race + '\n')
            save_file.write('Gender: ' + self.gender + '\n')
            save_file.write('Profession: ' + self.profession + '\n')
            save_file.write('Constitution: ' + str(self.cons) + '\n')
            save_file.write('Endurance: ' + str(self.endu) + '\n')
            save_file.write('Pneuma: ' + str(self.pneu) + '\n')
            save_file.write('Resiliance: ' + str(self.resi) + '\n')
            save_file.write('Resolution: ' + str(self.reso) + '\n')
            save_file.write('Providence: ' + str(self.prov) + '\n')
            save_file.write('Cons Mult: ' + str(self.cons_mult) + '\n')
            save_file.write('Endu Mult: ' + str(self.endu_mult) + '\n')
            save_file.write('Pneu Mult: ' + str(self.pneu_mult) + '\n')
            save_file.write('Resi Mult: ' + str(self.resi_mult) + '\n')
            save_file.write('Reso Mult: ' + str(self.reso_mult) + '\n')
            save_file.write('Prov Mult: ' + str(self.prov_mult) + '\n')
            save_file.write('X Pos: ' + str(self.x) + '\n')
            save_file.write('Y Pos: ' + str(self.y) + '\n')
            save_file.write('Base Hit Points: ' + str(self.base_hp) + '\n')
            save_file.write('Current Hit Points: ' + str(self.cur_hp) + '\n')
            save_file.write('Base Energy Points: ' + str(self.base_ep) + '\n')
            save_file.write('Current Energy Points: ' + str(self.cur_ep) + '\n')
            save_file.write('Base Pneuma Points: ' + str(self.base_pp) + '\n')
            save_file.write('Current Pneuma Points: ' + str(self.cur_pp) + '\n')
            save_file.write('Base Walk Speed: ' + str(self.base_walk_speed) + '\n')
            save_file.write('Base Run Multiplier: ' + str(self.base_run_mult) + '\n')

    def update(self):
        
        keys = pygame.key.get_pressed()

        if keys[pygame.K_LSHIFT]:
            self.running = True
        else:
            self.running = False

        diagonal_mult = 1.0
        if (keys[pygame.K_a] or keys[pygame.K_d]) and \
           (keys[pygame.K_w] or keys[pygame.K_s]):
            diagonal_mult = 1.06625

        if not self.immobile:
            if self.running:
                change = int(self.walk_speed * self.run_mult * utils.delta * diagonal_mult)
            else:
                change = int(self.walk_speed * utils.delta * diagonal_mult)

        if keys[pygame.K_a]:
            self.pos = self.x, self.y = (self.x - change, self.y)
        if keys[pygame.K_d]:
            self.pos = self.x, self.y = (self.x + change, self.y)
        if keys[pygame.K_w]:
            self.pos = self.x, self.y = (self.x, self.y - change)
        if keys[pygame.K_s]:
            self.pos = self.x, self.y = (self.x, self.y + change)

        self.walk_time += utils.delta

        if False:
            pass
        elif keys[pygame.K_d]:
            self.surface.fill( (0, 0, 0, 0) )
            if self.walk_time < 250:
                self.surface.blit( self.right0, (0, 0) )
            elif self.walk_time >= 250 and self.walk_time < 500:
                self.surface.blit( self.right1, (0, 0) )
            elif self.walk_time >= 500 and self.walk_time < 750:
                self.surface.blit( self.right2, (0, 0) )
            elif self.walk_time >= 750 and self.walk_time < 1000:
                self.surface.blit( self.right3, (0, 0) )
            elif self.walk_time >= 500:
                self.walk_time = utils.delta
                self.surface.blit( self.right0, (0, 0) )
        elif keys[pygame.K_a]:
            self.surface.fill( (0, 0, 0, 0) )
            if self.walk_time < 250:
                self.surface.blit( self.left0, (0, 0) )
            elif self.walk_time >= 250 and self.walk_time < 500:
                self.surface.blit( self.left1, (0, 0) )
            elif self.walk_time >= 500 and self.walk_time < 750:
                self.surface.blit( self.left2, (0, 0) )
            elif self.walk_time >= 750 and self.walk_time < 1000:
                self.surface.blit( self.left3, (0, 0) )
            elif self.walk_time >= 500:
                self.walk_time = utils.delta
                self.surface.blit( self.left0, (0, 0) )
        elif not (keys[pygame.K_d] or keys[pygame.K_a] or \
        keys[pygame.K_w] or keys[pygame.K_s]):
            self.surface.fill( (0, 0, 0, 0) )
            self.surface.blit( self.down0, (0, 0) )
            self.walk_time = utils.delta

    def blit(self, dest):
        dest.blit( self.surface, self.blit_pos )

    def blit_at(self, dest, pos):
        dest.blit( self.surface, pos )
