import game_framework
from pico2d import *


import main_state
import title_state


name = "RangkingState"
image = None

def enter():
    global image
    image = load_image('blackboard.png')

def exit():
    global image
    del(image)


def pause():
    pass

def resume():
    pass


def handle_events(frame_time):
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            game_framework.quit()
        else:
            if (event.type, event.key) == (SDL_KEYDOWN, SDLK_ESCAPE):
                game_framework.change_state(title_state)
            elif (event.type, event.key) == (SDL_KEYDOWN, SDLK_SPACE):
                game_framework.change_state(main_state)



def update(frame_time):
    pass


def draw(frame_time):
    global image
    x, y, time = 0, 0, 0
    module = {}

    f= open('save.txt','r')
    [x,y,time,
     ] = json.load(f)
    f.close()

    clear_canvas()
    image.draw(400, 300)
    font = load_font('ENCR10B.TTF')
    font.draw(400,300,'Time:%3.2f'% time,(255,255,255))
    font.draw(400, 200, 'PositionX:%3.2f' % x, (255, 255, 255))
    font.draw(400, 100, 'PositionY:%3.2f' % y, (255, 255, 255))

    #font.draw(self.x - 50, self.y + 40, 'Time: %3.2f' % self.life_time)
    update_canvas()



