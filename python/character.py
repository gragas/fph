import pygame

from buffalo import utils

class Character(object):
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
            running,
            gender,
            base_hp,
            base_ep,
            base_pp,
            base_walk_speed,
            base_run_mult,
            ):
        self.name = name
        self.race = race
        self.profession = profession
        self.cons = cons
        self.endu = endu
        self.pneu = pneu
        self.resi = resi
        self.reso = reso
        self.prov = prov
        self.cons_mult = cons_mult
        self.endu_mult = endu_mult
        self.pneu_mult = pneu_mult
        self.resi_mult = resi_mult
        self.reso_mult = reso_mult
        self.prov_mult = prov_mult
        self.pos = self.x, self.y = pos
        self.running = running
        self.gender = gender
        self.base_hp = base_hp
        self.base_ep = base_ep
        self.base_pp = base_pp
        self.base_walk_speed = base_walk_speed
        self.base_run_mult = base_run_mult
        self.calculate_maximums()
        self.set_maximums()
        # Load an image of the character
        self.surface = None
        self.hp_shield = 0.0

    def calculate_attribute_bonuses(self):
        # Calculate bonuses based on race, profession, equipped items, etc.
        pass

    def calculate_maximums(self):
        self.calculate_attribute_bonuses()
        self.max_hp = self.base_hp + \
                      self.cons_mult * self.cons + \
                      self.resi_mult * self.resi + \
                      self.prov_mult * self.prov
        self.max_ep = self.base_ep + \
                      self.endu_mult * self.endu + \
                      self.resi_mult * self.resi + \
                      self.reso_mult * self.reso
        self.max_pp = self.base_pp + \
                      self.pneu_mult * self.pneu + \
                      self.reso_mult * self.reso + \
                      self.prov_mult * self.prov

    def set_maximums(self):
        self.cur_hp = self.max_hp
        self.cur_ep = self.max_ep
        self.cur_pp = self.max_pp

    def update(self):
        raise NotImplementedError("The update(self) method has not been implemented for this class.")

    def blit(self, dest):
        dest.blit(self.surface, self.pos)
