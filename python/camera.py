from random import random

import pygame
import pygame.draw

from buffalo import utils

def init():
    
    global TILE_SIZE, SURFACE_SIZE
    global SW_IN_TILES, SH_IN_TILES
    global BOARDER_SIZE, BLIT_POSITION

    TILE_SIZE = 32
    BOARDER_SIZE = 0
    SURFACE_SIZE = (
        utils.SCREEN_W + 2 * BOARDER_SIZE * TILE_SIZE,
        utils.SCREEN_H + 2 * BOARDER_SIZE * TILE_SIZE
        )
    SW_IN_TILES = utils.SCREEN_W // TILE_SIZE
    SH_IN_TILES = utils.SCREEN_H // TILE_SIZE
    if not utils.SCREEN_W % TILE_SIZE == 0:
        SW_IN_TILES += 1
    if not utils.SCREEN_H % TILE_SIZE == 0:
        SH_IN_TILES += 1
    BLIT_POSITION = (-BOARDER_SIZE * TILE_SIZE + 100, -BOARDER_SIZE * TILE_SIZE + 100)
    
    global zero, one, two
    
    zero = utils.empty_surface( SURFACE_SIZE )
    one = utils.empty_surface( SURFACE_SIZE )
    two = utils.empty_surface( SURFACE_SIZE )

    # Fill zero with randomly colored tiles
    for y in range(SH_IN_TILES):
        for x in range(SW_IN_TILES):
            pygame.draw.rect( zero,
                              (
                                  int(random() * 256),
                                  int(random() * 256),
                                  int(random() * 256),
                                  255
                              ),
                              ( x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE )
                          )
