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
            cons_mult,
            endu_mult,
            pneu_mult,
            resi_mult,
            reso_mult,
            prov_mult,
            pos,
            base_hp,
            base_ep,
            base_pp,
            running,
            walk_speed,
            run_mult,
            ):
        super(Player, self).__init__(
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
            cons_mult,
            endu_mult,
            pneu_mult,
            resi_mult,
            reso_mult,
            prov_mult,
            pos,
            base_hp,
            base_ep,
            base_pp,
            running,
            walk_speed,
            run_mult,
        )
        
    def update(self):
        if not self.immobile:
            if self.running:
                change = int(self.walk_speed * self.run_mult * utils.delta)
            else:
                change = int(self.walk_speed * utils.delta)

        keys = pygame.key.get_pressed()
        if keys[pygame.K_a]:
            self.pos = self.x, self.y = (self.x - change, self.y)
        if keys[pygame.K_d]:
            self.pos = self.x, self.y = (self.x + change, self.y)
        if keys[pygame.K_w]:
            self.pos = self.x, self.y = (self.x, self.y - change)
        if keys[pygame.K_s]:
            self.pos = self.x, self.y = (self.x, self.y + change)
