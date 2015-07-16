import pygame
import pygame.font

def init( logic_func=None, render_func=None ):

    global SCREEN_W, SCREEN_H
    global SCREEN_S, SCREEN_M
    global screen
    global clock
    global end

    pygame.init()

    dinf = pygame.display.Info()
    SCREEN_S = SCREEN_W, SCREEN_H = (dinf.current_w, dinf.current_h)
    SCREEN_M = (SCREEN_W / 2, SCREEN_H / 2)

    screen = pygame.display.set_mode(SCREEN_S, pygame.FULLSCREEN)
    clock  = pygame.time.Clock()

    end = False

    pygame.display.set_caption("FPH")
    
    global CLEAR_COLOR
    global CAP_FRAME_RATE
    global FRAMES_PER_SECOND    

    CLEAR_COLOR = (0, 0, 0, 0)
    CAP_FRAME_RATE = False
    FRAMES_PER_SECOND = 120
    
    global logic
    global render    

    logic = logic_func
    render = render_func

    global delta
    delta = 1000
    
    pygame.font.init()
    
    global DEFAULT_FONT
    global fonts
    DEFAULT_FONT = "arial"
    fonts = { 
        'default': pygame.font.SysFont(DEFAULT_FONT, 18),
        'droidsans14': pygame.font.SysFont("droidsans", 18),
        }
