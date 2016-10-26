import sys
import math
sys.path.append('../2dgample')

import random
from pico2d import *

menu = None
running = None
break_check = None

# state

LEFT, UP, RIGHT, DOWN, NORMAL,JUMP,SURF,DOWNRIGHT = 4, 8, 6, 2, 0,7,10,8

KeyDown = None
break_status = None
break_status1 = None
#KeyDown = {LEFT,UP,RIGHT,DOWN,NORMAL}


class BackGround:
    image = None

    def draw(self):
        self.image.draw(self.x,self.y,800,600)

    def __init__(self):
        self.x, self.y = 400,300   # init positon player
        self.frame = random.randint(0, 7)
        self.run_frames = 0
        self.stand_frames = 0
        self.state = 0
        if BackGround.image == None:
            BackGround.image = load_image('Base Background10.png')

    def update(self):
        self.x -= 20
        self.frame = (self.frame + 1) % 60
        if self.x <= -800:
            self.x = 800



class Player:
    global space
    space = None
    image = None


    LEFT,UP,RIGHT,DOWN,NORMAL,JUMP,DOWNRIGHT = 4, 8, 6, 2, 0, 7, 8

    def handle_left_run(self):
        self.x -= 10
        self.run_frames += 1
        self.state_update()
        if self.x < 0:
            pass  # state dead

    def handle_right_run(self):
        self.x += 10
        self. run_frames += 1
        self.state_update()

    def handle_up_run(self):
        self.y += 10
        self.run_frames += 1
        self.state_update()
        if  700 < self.y:
            pass # jump

    def handle_down_run(self):
        self.y -= 10
        self.run_frames += 1
        self.state_update()

        if self.y < 50:
            pass  # dead

    def handle_downright(self):
        self.y -= 10
        self.x += 10
        self.run_frames += 1
        self.state_update()

    def handle_normal(self):
        self.run_frames += 1
        self.x += 1
        self.state_update()

        pass # self.run_frame += 1

    def handle_surf(self):
        self.x += 5
        self.run_frames += 1
        #self.state_update()


    def handle_jump(self):
        x = 0
        y = 0
        r = 3
        x += 1
        y += 4
        self.x += 4
        self.y= self.y+ r * math.sin(y)
        self.state_update()
    handle_state = {
                LEFT: handle_left_run,
                RIGHT: handle_right_run,
                DOWN: handle_down_run,
                UP: handle_up_run,
                NORMAL: handle_normal,
                JUMP: handle_jump,
                SURF: handle_surf,
                DOWNRIGHT :handle_downright
    }

    def update(self):
        global break_check
        self.frame = (self.frame + 1) % 8
        self.state_update()
        self.handle_state[self.state](self)
        if(break_check == True):
            self.state = SURF

       # if(space == True)

    def __init__(self):
        self.x, self.y = 0, 400  # init positon player
        self.frame = random.randint(0,7)
        self.run_frames = 0
        self.stand_frames = 0
        self.state = self.NORMAL
        if Player.image == None:
            Player.image = load_image('runorange_animation copy.png')

    def draw(self):
        global break_status
        cnt = 0
        if break_status and cnt <= 1:
            if cnt <= 6:
                cnt = 0
                break_status = False
            ++cnt
            return
        self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

    def state_update(self):
        global KeyDown
        global space


       # if space == True:
        #    self.state = SURF
         #   return
        if KeyDown == LEFT:
            self.state = LEFT
        elif KeyDown == JUMP:
            self.state = JUMP
        elif KeyDown == RIGHT:
            self.state = RIGHT
        elif KeyDown == UP:
            self.state = UP
        elif KeyDown == DOWN:
            self.state = DOWN
        elif KeyDown == DOWN:
            self.state = DOWNRIGHT
        elif space == True:
            self.state = SURF
            return
        else:
            self.state = NORMAL
        KeyDown = NORMAL




class  Ball:
    image = None

    def __init__(self):
        self.x, self.y = 820, 400

        if Ball.image == None:
            Ball.image = load_image('Beach_Ball-2.png')
    def update(self):
        self.x -= 5
    def draw(self):
       self.image.draw(self.x, self.y)

       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  Fruits:
    image = None

    def __init__(self):
        self.x, self.y = 600, 400

        if Fruits.image == None:
            Fruits.image = load_image('pear.png')
    def update(self):
        self.x -= 5
    def draw(self):
       global break_status1

       self.image.draw(self.x, self.y,50,50)
       if break_status1 == True :
           Fruits.image = load_image('pear-change.png')
           self.y -= 5
           self.update()
           break_status1 = False
           return
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  Bucket:
    image = None

    def __init__(self):
        self.x, self.y = 820, 100

        if Bucket.image == None:
            Bucket.image = load_image('bucket-1.png')
    def update(self):
        self.x -= 5

    def draw(self):
       self.image.draw(self.x, self.y,100,100)
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  Sun:
    image = None

    def __init__(self):
        self.x, self.y = 820, 600

        if Sun.image == None:
            Sun.image = load_image('sun.png')
    def update(self):
        self.x -= 0.1

    def draw(self):
       self.image.draw(self.x, self.y)

class  Cloud:
    image = None

    def __init__(self):
        self.x, self.y = 400, 650

        if Cloud.image == None:
            Cloud.image = load_image('cloud.png')
    def update(self):
        self.x -= 1

    def draw(self):
       self.image.draw(self.x, self.y)

class  Direction:
    image = None

    def __init__(self):
        self.x, self.y = 100, 100

        if Direction.image == None:
            Direction.image = load_image('direction.png')
    def update(self):
        self.x
    def draw(self):
       self.image.draw(self.x, self.y,200,200)

class Tree:
    image = None

    def __init__(self):
        self.x, self.y = 1500, -70

        if Tree.image == None:
            Tree.image = load_image('Palm_Tree_Large.png')
    def update(self):
        self.x -= 5

    def draw(self):
       self.image.draw(self.x, self.y)
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)


class Bird:
    image = None
    NORMAL, STOP_MOVE = 1, 0


    def __init__(self):
        self.x, self.y = 800, random.randint(400,500)

        if Bird.image == None:
            Bird.image = load_image('Bird-2.png')


    def update(self):
        self.x -= 12

       #self.frame = (self.frame + 1) % 8

    def draw(self):
       self.image.draw(self.x, self.y)
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class CMenu:
    image = None
    global selectMenu


    def __init__(self):
        self.x,self.y = 400,300

        if CMenu.image == None:
            CMenu.image = load_image('juicyWave1 copy.png')

    def update(self):
        pass

    def draw(self):
       self.image.draw(self.x, self.y,800,600)

    def menuset(self):
        global menu
        global selectMenu

        if selectMenu == True:
            menu = True

class KPU:

    image = None

    def __init__(self):
        self.x,self.y = 400, 300

        if KPU.image == None:
            KPU.image = load_image('kpu_credit.png')

    def draw(self):
         self.image.draw(self.x, self.y)

def handle_events():
    global running
    global menu
    global space
    global KeyDown

    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            running = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            running = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_SPACE:
            menu = False
            space = True
        elif event.type == SDL_KEYUP and event.key == SDLK_SPACE:
            space = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_RIGHT:
            KeyDown = RIGHT
        elif event.type == SDL_KEYDOWN and event.key == SDLK_LEFT:
            KeyDown = LEFT
        elif event.type == SDL_KEYDOWN and event.key == SDLK_UP:
            KeyDown = UP
        elif event.type == SDL_KEYDOWN and event.key == SDLK_DOWN:
            KeyDown = DOWN
        elif event.type == SDL_KEYDOWN and event.key == SDLK_DOWN and SDLK_RIGHT:
            KeyDown = DOWNRIGHT


def break_check(player,ball ):
    global running
    global break_status
    if player.x >= ball.x -50 and player.x <= ball.x +50 and player.y >= ball.y -50 and player.y <= ball.y +50 :
        break_status = True

def break_check1(player,fruit ):
    global running
    global break_status1
    if player.x >= fruit.x -50 and player.x <= fruit.x +50 and player.y >= fruit.y -50 and player.y <= fruit.y +50:
        break_status1 = True


def main():

    open_canvas()


    mainMenu = CMenu()
    player = Player()
    tree = Tree()
    ball = Ball()
    background = BackGround()
    background1 = BackGround()
    background2 = BackGround()
    background3 = BackGround()
    background1.x = background.x + 800
    bird = Bird()
    sun = Sun()
    cloud = Cloud()
    bucket = Bucket()
    pear = Fruits()
    kpu = KPU()
    direction = Direction()

    clear_canvas()
    kpu.draw()
    update_canvas()
    delay(2.0)

    global menu
    global running
   # global space
    menu = True

    while menu:
        handle_events()
        clear_canvas()
        mainMenu.draw()
        update_canvas()

    running = True

    while running:
        handle_events()
        clear_canvas()

        player.update()
        bird.update()
        tree.update()
        ball.update()
        sun.update()
        cloud.update()
        bucket.update()
        direction.update()
        pear.update()

        background2.x = background1.x + 800
        background3.x = background2.x + 800
        background.update()
        background1.update()
        background2.update()
        background3.update()

        break_check(player,ball)
        break_check1(player,pear)

        background.draw()
        background1.draw()
        background2.draw()
        background3.draw()


        tree.draw()
        player.draw()
        bird.draw()
        ball.draw()
        sun.draw()
        cloud.draw()
        bucket.draw()
        direction.draw()
        pear.draw()

        update_canvas()

        delay(0.04)

    close_canvas()


if __name__ == '__main__':
    main()