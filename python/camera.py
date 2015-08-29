from random import random

import pygame
import pygame.draw

from buffalo import utils

def init():
    
    global TILE_SIZE, SURFACE_SIZE
    global SW_IN_TILES, SH_IN_TILES
    global BOARDER_SIZE, BLIT_POSITION

    TILE_SIZE = 32
    BOARDER_SIZE = 10
    NUM_TILES_SW = utils.SCREEN_W // TILE_SIZE
    NUM_TILES_SH = utils.SCREEN_H // TILE_SIZE
    if not utils.SCREEN_W % TILE_SIZE == 0:
        NUM_TILES_SW += 1
    if not utils.SCREEN_H % TILE_SIZE == 0:
        NUM_TILES_SH += 1
    SURFACE_SIZE = (
        (NUM_TILES_SW + 2 * BOARDER_SIZE) * TILE_SIZE,
        (NUM_TILES_SH + 2 * BOARDER_SIZE) * TILE_SIZE,
        )
    BLIT_POSITION = (-BOARDER_SIZE * TILE_SIZE, -BOARDER_SIZE * TILE_SIZE)
    
    global zero, one, two
    
    zero = utils.empty_surface( SURFACE_SIZE )
    one = utils.empty_surface( SURFACE_SIZE )
    two = utils.empty_surface( SURFACE_SIZE )

    global LOCK_TO_PLAYER
    LOCK_TO_PLAYER = True

    # Fill zero with randomly colored tiles
    for y in range(
            0,
            SURFACE_SIZE[1] + TILE_SIZE,
            TILE_SIZE
    ):
        for x in range(
                0,
                SURFACE_SIZE[0] + TILE_SIZE,
                TILE_SIZE
        ):
            pygame.draw.rect( zero,
                              (
                                  int(random() * 50) + 50,
                                  int(random() * 50) + 150,
                                  int(random() * 50) + 50,
                                  255
                              ),
                              ( x, y, TILE_SIZE, TILE_SIZE )
                          )

def update():
    if self.LOCK_TO_PLAYER:
        pass
