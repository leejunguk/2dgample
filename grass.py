import random

from pico2d import *

class Grass:
    def __init__(self):
        self.image = load_image('grass.png')

    def draw(self):
        self.image.draw(400, 30)

    def get_bb(self):
        return 0, 0, 800, 50
    # fill here

