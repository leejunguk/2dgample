import sys
import math
sys.path.append('../2dgample')
from pico2d import *

import random
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
            BackGround.image = load_image('animated_bg12 copy1.png')

    def update(self):
        self.x -= 20
        self.frame = (self.frame + 1) % 60
        if self.x <= -800:
            self.x = 800