import sys
sys.path.append('../LabsAll/Labs')

import random
from pico2d import *

running = None
rest = None
direction = None
space = None
wave = None


class Grass:
    def __init__(self):
        self.image = load_image('grass.png')

    def draw(self):
        self.image.draw(400, 30)


class Boy:
    image = None
    global space

    LEFT_RUN, RIGHT_RUN, LEFT_STAND, RIGHT_STAND = 0, 1, 2, 3


    def handle_left_run(self):
        global space
        self.x -= 5
        self.run_frames += 1
        if self.x < 0:
            self.state = self.RIGHT_STAND
            self.x = 0
        if self.run_frames == 100:
            self.state = self.LEFT_STAND
            self.stand_frames = 0
        if space == True:
            self.state = self.RIGHT_RUN
            self.run_frames = 0
            space = False

    def handle_left_stand(self):
        global space
        self.stand_frames += 1
        if self.stand_frames == 50:
            self.state = self.LEFT_RUN
            self.run_frames = 0
        if space == True:
            self.state = self.LEFT_RUN
            self.run_frames = 0
            space = False


    def handle_right_run(self):
        global space
        self.x += 5
        self.run_frames += 1
        if self.x > 800:
            self.state = self.LEFT_RUN
            self.x = 800
        if self.run_frames == 100:
            self.state = self.RIGHT_STAND
            self.stand_frames = 0
        if space == True:
            self.state = self.LEFT_RUN
            self.run_frames = 0
            space = False


    def handle_right_stand(self):
        global space
        self.stand_frames += 1
        if self.stand_frames == 50:
            self.state = self.RIGHT_RUN
            self.run_frames = 0
        if space == True:
            self.state = self.RIGHT_RUN
            self.run_frames = 0
            space = False

    handle_state = {
                LEFT_RUN: handle_left_run,
                RIGHT_RUN: handle_right_run,
                LEFT_STAND: handle_left_stand,
                RIGHT_STAND: handle_right_stand
    }


    def update(self):
        self.frame = (self.frame + 1) % 8
        self.handle_state[self.state](self)



    def __init__(self):
        self.x, self.y = random.randint(100, 700), 90
        self.frame = random.randint(0, 7)
        self.run_frames = 0
        self.stand_frames = 0
        self.state = self.RIGHT_RUN
        if Boy.image == None:
            Boy.image = load_image('animation_sheet.png')

    def draw(self):
        self.image.clip_draw(self.frame * 100, self.state * 100, 100, 100, self.x, self.y)


def handle_events():
    global running
    global space
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            running = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            running = False
        elif event.type == SDL_KEYDOWN and event.key == SDLK_SPACE:
            space = True



def main():



    open_canvas()

    boy = Boy()
    grass = Grass()

    global running
    global space
    running = True

    while running:
        handle_events()

        boy.update()
        # bluewave.clip_draw(frame * 400, 20, 235, 300, x, 0)
        # headerwave.clip_draw(frame* 400 ,40, 600, 100 , 300,200)

        # 특정한 정수를 반복할때. 나머지 연산
        # if문 보다 이해하기 편함.
        # x += 15
        get_events()
        clear_canvas()
        Background.draw(400, 300)
        frame = (frame + 1) % 4
        wave.clip_draw(frame * 400, 20, 235, 300, 80, 330)
        grass.draw()
        boy.draw()
        update_canvas()

        delay(0.04)

    close_canvas()


if __name__ == '__main__':
    main()







# 여기를 채우세요.


