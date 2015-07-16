import pygame
import utils

import menu

def main():

    while not utils.end:    
        utils.logic()
        utils.update()
        utils.render()
        utils.delta = utils.clock.tick( utils.FRAMES_PER_SECOND )

if __name__ == "__main__":
    
    utils.init( 
        logic_func=menu.logic, 
        update_func=menu.update, 
        render_func=menu.render 
        )
    menu.init()
    main()

    pygame.quit()
