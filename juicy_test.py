import sys
import math
sys.path.append('../2dgample')

import platform
import os
import game_framework

if platform.architecture()[0] == '32bit':
    os.environ["PYSDL2_DLL_PATH"] = "./SDL2/x86"
else:
    os.environ["PYSDL@_DLL_PATH"] = "./SDL2/x64"

import random
from BackGround import BackGround
from pico2d import *

space = None
menu = None
running = None
break_check = None
number_life = None
gravity = None
isFinish = None
TotalScore = 0
isGameFinish = None
eat_sound = None
background_sound  = None
isGameClear = None
Life = 50




# state
SURF =22
LEFT, UP, RIGHT, DOWN, NORMAL,JUMP,DOWNRIGHT = 4, 8, 6, 2, 0,7,8
birdRight = 10
KeyDown = None
break_status = None
break_status1 = None
#KeyDown = {LEFT,UP,RIGHT,DOWN,NORMAL}






class Player:
    global space
    global gravity


    image = None

    PIXEL_PER_METER = (10.0 / 0.3)
    RUN_SPEED_KMPH = 1.0
    RUN_SPEED_MPM = (RUN_SPEED_KMPH * 1000.0 / 60.0)
    RUN_SPEED_MPS = (RUN_SPEED_MPM / 60.0)
    RUN_SPEED_PPS = (RUN_SPEED_MPS * PIXEL_PER_METER)

    SURF, LEFT, UP, RIGHT, DOWN, NORMAL, JUMP,DOWNRIGHT = 22, 4, 8, 6, 2, 0, 7, 11

    def handle_left_run(self):
        self.x -= 10
        self.run_frames += 1
        self.state_update(frame_time)


    def handle_right_run(self):
        self.x += 10
        self. run_frames += 1
        self.state_update(frame_time)
        pass

    def handle_up_run(self):
        self.y += 10
        self.run_frames += 1
        self.state_update(frame_time)


    def handle_down_run(self):
        self.y -= 10
        self.run_frames += 1
        self.state_update(frame_time)

        if self.y < 50:
            pass  # dead

    def handle_downright(self):
        self.y -= 10
        self.x += 10
        self.run_frames += 1
        self.state_update(frame_time)

    def handle_normal(self):
        global gravity
        global isFinish
        global isGameFinish
        global isGameClear
        global frame_time
        self.y -= 4

        if 600 <= self.x:
            isGameClear = True

        self.run_frames += 1
        if gravity == True:
            self.x += 0.5
            self.radian += 0.1
            self.y += 10 * math.cos(self.radian) +4
            if 3 <= self.radian:
                isFinish = True
            if self.y <= 400 and isFinish == True:
                gravity = False
                isFinish = False
                self.radian = 0
        elif space == True:
            distance = Player.RUN_SPEED_PPS * frame_time
            self.x += (distance)
            self.spaceradian += 0.1
            self.y += 10 * math.sin(self.spaceradian) + 4
            if 3<= self.spaceradian:
                self.spaceradian =0

            if 400<= self.y:
                gravity = True
                self.spaceradian =0
        elif 400 <= self.y:
            self.y += 10 * math.sin(self.x)
            if 400<= self.y:
                gravity = True

        pass # self.run_frame += 1

    def Drop(self):
        self.y -= 10 * math.sin(self.x)

    def handle_surf(self):
        self.run_frames += 1
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x += (distance)
        self.y -= 10 * math.sin(self.x)



    def handle_jump(self):
        x = 0
        y = 0
        r = 3
        x += 1
        y += 4
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x += (distance)
        self.y= self.y+ r * math.sin(y)

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

    def update(self, frame_time):
        global break_check

        self.frame = (self.frame + 1) % 8
        self.state_update(frame_time)
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x += (distance)
        self.y -= (distance)
        self.handle_state[self.state](self)


       # if(space == True)

    def __init__(self):
        self.x, self.y = 0, 400  # init positon player
        self.frame = random.randint(0,7)
        self.run_frames = 0
        self.stand_frames = 0
        self.radian = 0
        self.spaceradian = 0
        self.downradian = 0
        self.state = self.NORMAL
        if Player.image == None:
            Player.image = load_image('runorange_animation copy.png')

    def draw(self):
        global break_status
        global Life
        cnt = 0
        if break_status and cnt <= 1:


            if cnt <= 6:
                cnt = 0
                break_status = False
            ++cnt
            Life -= 1
            return
        self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

    def state_update(self,frame_time):
        global KeyDown
        global isGameFinish

        if self.y <= 120:
            isGameFinish = False


       # if space == True:
        #    self.state = SURF
         #   return

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




class  Ball:
    image = None

    def __init__(self):
        self.x, self.y = random.randint(400, 8000), random.randint(200, 400)

        if Ball.image == None:
            Ball.image = load_image('Beach_Ball-2.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 5
    def draw(self):
       self.image.draw(self.x, self.y)

       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  JellyFish:
    image = None

    def __init__(self):
        self.x, self.y = random.randint(400, 8000), random.randint(200, 400)

        if JellyFish.image == None:
            JellyFish.image = load_image('Jellyfish.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 10
    def draw(self):
       self.image.draw(self.x, self.y)

       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  Apple:
    image = None

    def __init__(self):
        self.x, self.y = random.randint(400,8000), random.randint(200,400)
        self.image_change = False
        self.image = load_image('Apple.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 10
        if break_status1 == True:
            pass # self.x,self.y = break_check1(Player, Fruits)
        #if self.image_change == True:
        #    self.image = load_image('pear-change.png')

    def Move(self):
        pass

    def draw(self):
       global break_status1
       if self.image ==None:
           return
       self.image.draw(self.x, self.y,50,50)

       if break_status1 == True :


           self.image_change = True
           break_status1 = False
           return




class  Fruits:
    image = None


    def __init__(self):
        self.x, self.y = random.randint(400,8000), random.randint(200,400)
        self.image_change = False
        self.image = load_image('pear.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 10
        if break_status1 == True:
            pass # self.x,self.y = break_check1(Player, Fruits)
        #if self.image_change == True:
        #    self.image = load_image('pear-change.png')

    def Move(self):
        pass

    def draw(self):
       global break_status1
       if self.image ==None:
           return
       self.image.draw(self.x, self.y,50,50)

       if break_status1 == True :

           self.image_change = True
           break_status1 = False
           return

       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  Bucket:
    image = None

    def __init__(self):
        self.x, self.y = 820, 100

        if Bucket.image == None:
            Bucket.image = load_image('bucket-1.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 10

    def draw(self):
       self.image.draw(self.x, self.y,100,100)
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)

class  Sun:
    image = None

    def __init__(self):
        self.x, self.y = 820, 600

        if Sun.image == None:
            Sun.image = load_image('sun.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 0.1

    def draw(self):
       self.image.draw(self.x, self.y)

class  Cloud:
    image = None

    def __init__(self):
        self.x, self.y = 400, 650

        if Cloud.image == None:
            Cloud.image = load_image('cloud.png')
    def update(self,frame_time):
        self.x -= 1

    def draw(self):
       self.image.draw(self.x, self.y)

class  Direction:
    image = None

    def __init__(self):
        self.x, self.y = 100, 100

        if Direction.image == None:
            Direction.image = load_image('direction.png')
    def update(self,frame_time):
        self.x
    def draw(self):
       self.image.draw(self.x, self.y,200,200)

class Tree:
    image = None

    def __init__(self):
        self.x, self.y = 1500, -70

        if Tree.image == None:
            Tree.image = load_image('Palm_Tree_Large.png')
    def update(self,frame_time):
        distance = Player.RUN_SPEED_PPS * frame_time
        self.x -= (distance) * 3

    def draw(self):
       self.image.draw(self.x, self.y)
       # self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)


class Bird:
    image = None
    NORMAL, STOP_MOVE, birdRight = 1, 0, 2
    State = NORMAL

    def __init__(self):
        self.x, self.y = 800, random.randint(450,550)

        if Bird.image == None:
            Bird.image = load_image('Bird-2.png')

        self.State = NORMAL

    def update(self,frame_time):

        if(self.State ==NORMAL):
            distance = Player.RUN_SPEED_PPS * frame_time
            self.x -= (distance) *12
            if(self.x <= 0):
                self.State = birdRight
                Bird.image = load_image('Bird-2_vertical.png')
        if (self.State == birdRight):
            distance = Player.RUN_SPEED_PPS * frame_time
            self.x += (distance) *12
            if (self.x >= 800):
                self.State = NORMAL
                Bird.image = load_image('Bird-2.png')
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
            CMenu.image = load_image('juicyWave1_START.png')

    def update(self,frame_time):
        pass

    def draw(self):
       self.image.draw(self.x, self.y,800,600)


    def menuset(self):
        global menu
        global selectMenu

        if selectMenu == True:
            menu = True

class CMusic:

    def __init__(self):
        global background_sound
        self.bgm = None
        self.bgm = load_music('JuicyStartSound.wav')
        self.bgm.set_volume(35)
        self.bgm.repeat_play()




class CGameOverStage:
    image = None



    def __init__(self):
        self.x,self.y = 400,300

        if CGameOverStage.image == None:
            CGameOverStage.image = load_image('juicyWave1 GameOver.png')

    def update(self,frame_time):
        pass

    def draw(self):
       self.image.draw(self.x, self.y,800,600)

    def menuset(self):
        global menu
        #global selectMenu

        #if selectMenu == True:
         #   menu = True


class KPU:

    image = None

    def __init__(self):
        self.x,self.y = 400, 300

        if KPU.image == None:
            KPU.image = load_image('kpu_credit.png')

    def draw(self):
         self.image.draw(self.x, self.y)

class GameClear:

    image = None

    def __init__(self):
        self.x,self.y = 400, 300

        if GameClear.image == None:
            GameClear.image = load_image('Game Clear.png')

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
        if event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            running = False
        if event.type == SDL_KEYDOWN and event.key == SDLK_SPACE:
            menu = False
            space = True
        if event.type == SDL_KEYUP and event.key == SDLK_SPACE:
            space = False
        if event.type == SDL_KEYDOWN and event.key == SDLK_RIGHT:
            KeyDown = RIGHT
        if event.type == SDL_KEYDOWN and event.key == SDLK_LEFT:
            KeyDown = LEFT
        if event.type == SDL_KEYDOWN and event.key == SDLK_UP:
            KeyDown = UP
        if event.type == SDL_KEYDOWN and event.key == SDLK_DOWN:
            KeyDown = DOWN

def break_check_with_bird(player,Bird ):
    global running
    global break_status
    if player.x >= Bird.x -50 and player.x <= Bird.x +50 and player.y >= Bird.y -50 and player.y <= Bird.y +50 :
        break_status = True

def enter():
    print("TEst")
    bgm = load_music('JuicyStartSound.wav')
    bgm.set_volume(35)
    bgm.repeat_play()


def break_check(player,ball ):
    global running
    global break_status
    if player.x >= ball.x -50 and player.x <= ball.x +50 and player.y >= ball.y -50 and player.y <= ball.y +50 :
        break_status = True

def break_check1(Player,Fruits ):
    global running
    global break_status1
    global TotalScore
    global eat_sound
    turn = 0

    if Player.x >= Fruits.x -50 and Player.x <= Fruits.x +50 and Player.y >= Fruits.y -50 and Player.y <= Fruits.y +50:
        break_status1 = True
        #Fruits.x -= 100
        #Fruits.y -= 100
        Fruits.image =  load_image('pear-change.png')

        TotalScore += 10
        eat_sound.play()

def break_check2(Player, Fruits):
    global running
    global break_status1
    global TotalScore
    global eat_sound
    turn = 0

    if Player.x >= Fruits.x - 50 and Player.x <= Fruits.x + 50 and Player.y >= Fruits.y - 50 and Player.y <= Fruits.y + 50:
            break_status1 = True
            # Fruits.x -= 100
            # Fruits.y -= 100
            Fruits.image = load_image('Apple_change.png')

            TotalScore += 10
            eat_sound.play()

#def follow_check(plaver,fruit):
#    global break_status1
#    if break_status1 == True:
#        fruit.x =

current_time = 0.0


def get_frame_time():

    global current_time

    frame_time = get_time() - current_time
    current_time += frame_time
    return frame_time


def main():

    ball_number = 10
    open_canvas()

    font = load_font('ENCR10B.TTF', 40)

    mainMenu = CMenu()
    player = Player()
    tree = Tree()

    Jelly = [JellyFish() for i in range(ball_number)]
    balls = [Ball() for i in range(ball_number)]
    pears = [Fruits() for i in range(ball_number)]
    apples = [Apple() for i in range(ball_number)]

    background = BackGround()
    background1 = BackGround()
    background2 = BackGround()
    background3 = BackGround()
    background1.x = background.x + 800
    bird = Bird()
    sun = Sun()
    cloud = Cloud()
    bucket = Bucket()
   # pear = Fruits()
    kpu = KPU()
    gameover = CGameOverStage()
    direction = Direction()
    music = CMusic()

    clear_canvas()
    kpu.draw()
    update_canvas()
    delay(2.0)

    global menu
    global running
    global space
    global TotalScore
    global current_time
    global eat_sound
    global Life
    global frame_time

    eat_sound = load_wav('AppleSound.wav')
    eat_sound.set_volume(50)



    menu = True

    while menu:
     #   background_sound.bgm.repeat_play()
        handle_events()

        mainMenu.draw()
        update_canvas()

    running = True

    current_time = get_time()

    while running:
        handle_events()
        frame_time = get_frame_time()


        for i in range(ball_number):
            balls[i].update(frame_time)
            pears[i].update(frame_time)
            apples[i].update(frame_time)
            Jelly[i].update(frame_time)
            if pears[i].x <=-100:
                pears[i].image =None



        player.update(frame_time)
        bird.update(frame_time)
        tree.update(frame_time)

        sun.update(frame_time)
        cloud.update(frame_time)
        bucket.update(frame_time)
        direction.update(frame_time)
        #pear.update(frame_time)

        background2.x = background1.x + 800
        background3.x = background2.x + 800
        background.update()
        background1.update()
        background2.update()
        background3.update()

        for i in range(ball_number):
            break_check(player,balls[i])
            break_check1(player,pears[i])
            break_check2(player, apples[i])
            break_check(player, Jelly[i])

        break_check_with_bird(player,bird)


        background.draw()
        background1.draw()
        background2.draw()
        background3.draw()



        tree.draw()
        player.draw()
        bird.draw()
        for i in range(ball_number):
            balls[i].draw()
            Jelly[i].draw()
            pears[i].draw()
            apples[i].draw()

        sun.draw()
        cloud.draw()
        bucket.draw()
        direction.draw()
        font.draw(160, 580, "%r" % TotalScore, (255, 255, 0))
        font.draw(20, 580, 'Score:', (255, 255, 255))

        font.draw(720, 580, "%r" % Life, (255, 0, 0))
        font.draw(600, 580, 'Life:', (255, 255, 255))


        if isGameFinish == False or Life <=0:
            clear_canvas()
            gameover.draw()
            update_canvas()
            delay(2.0)
            break

        if isGameClear == True:
            clear_canvas()
            gameclear = GameClear()
            gameclear.draw()
            update_canvas()
            delay(2.0)
            break

        update_canvas()

        delay(0.04)

    close_canvas()


if __name__ == '__main__':
    main()