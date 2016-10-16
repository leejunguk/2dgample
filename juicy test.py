import sys
sys.path.append('../2dgample')

import random
from pico2d import *

running = None
# state

LEFT, UP, RIGHT, DOWN, NORMAL = 4, 8, 6, 2, 0

KeyDown = None
#KeyDown = {LEFT,UP,RIGHT,DOWN,NORMAL}


class BackGround:
    image = None

    def draw(self):
        self.image.clip_draw(self.frame * 20, self.state * 100, 800, 600, 400 , 300)

    def __init__(self):
        self.x, self.y = 10,0  # init positon player
        self.frame = random.randint(0, 7)
        self.run_frames = 0
        self.stand_frames = 0
        self.state = 0
        if BackGround.image == None:
            BackGround.image = load_image('background-4.png')

    def update(self):
        self.frame = (self.frame + 1) % 60



class Player:
    image = None

    LEFT,UP,RIGHT,DOWN,NORMAL = 4,8,6,2,0

    def handle_left_run(self):
        self.x -= 5
        self.run_frames += 1
        self.state_update()
        if self.x < 0:
            pass  # state dead

    def handle_right_run(self):
        self.x += 5
        self. run_frames += 1
        self.state_update()

    def handle_up_run(self):
        self.y += 5
        self.run_frames += 1
        self.state_update()
        if  700 < self.y:
            pass # jump

    def handle_down_run(self):
        self.y -= 5
        self.run_frames += 1
        self.state_update()

        if self.y < 50:
            pass  # dead

    def handle_normal(self):
        self.state_update()
        pass # self.run_frame += 1

    handle_state = {
                LEFT: handle_left_run,
                RIGHT: handle_right_run,
                DOWN: handle_down_run,
                UP: handle_up_run,
                NORMAL: handle_normal
    }

    def update(self):
        self.frame = (self.frame + 1) % 8
        self.state_update()
        self.handle_state[self.state](self)


    def __init__(self):
        self.x, self.y = 0, 400  # init positon player
        self.frame = random.randint(0,7)
        self.run_frames = 0
        self.stand_frames = 0
        self.state = self.NORMAL
        if Player.image == None:
            Player.image = load_image('runorange_animation copy.png')

    def draw(self):
        self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

    def state_update(self):
        global KeyDown

        if KeyDown == LEFT:
            self.state = LEFT
        elif KeyDown == RIGHT:
            self.state = RIGHT
        elif KeyDown == UP:
            self.state = UP
        elif KeyDown == DOWN:
            self.state = DOWN
        else:
            self.state = NORMAL
        KeyDown = NORMAL


class Bird:
    image = None
    NORMAL, STOP_MOVE = 1, 0


    def __init__(self):
        self.x, self.y = 800, random.randint(100,400)
        self.state = self.NORMAL

        if Bird.image == None:
            Bird.image = load_image('Bird.png')

    def move_normal(self):
        while self.x > 0:
            self.x -=5
            self.state = NORMAL

    def move_stop(self):
        self.x -= 0
        self.state = NORMAL

    def update(self):
        self.handle_state[self.state](self)
       #self.frame = (self.frame + 1) % 8

    def draw(self):
       self.image.draw(self.x, self.y)
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

    handle_state = {
        STOP_MOVE: move_stop,
        NORMAL: move_normal
    }


def handle_events():
    global running
    global space
    global KeyDown

    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            running = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            running = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_SPACE:
            space = True
        elif event.type == SDL_KEYDOWN and event.key == SDLK_RIGHT:
            KeyDown = RIGHT
        elif event.type == SDL_KEYDOWN and event.key == SDLK_LEFT:
            KeyDown = LEFT
        elif event.type == SDL_KEYDOWN and event.key == SDLK_UP:
            KeyDown = UP
        elif event.type == SDL_KEYDOWN and event.key == SDLK_DOWN:
            KeyDown = DOWN


def main():

    open_canvas()

    player = Player()
    background = BackGround()
    bird = Bird()

    global running
    global space

    running = True

    while running:
        handle_events()

        player.update()
        background.update()
        clear_canvas()
        background.draw()
        player.draw()
        bird.draw()

        update_canvas()

        delay(0.04)

    close_canvas()


if __name__ == '__main__':
    main()