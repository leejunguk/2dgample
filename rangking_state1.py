import game_framework
from pico2d import *


import main_state


name = "RankingState1"
image = None
font = None

def enter():
    global image,font
    image = load_image('blackboard.png')
    font = load_font('ENCR10B.TTF',40)

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
                game_framework.quit()



def update(frame_time):
    pass
def bubble_sort(data):
    for i in range(0,len(data)):
        for j in range (i+1, len(data)):
            if data[i]['Time'] < data[j]['Time']:
                data[i], data[j] = data[j], data[i]


def draw_rangking():
    f = open('data_file.txt', 'r')
    Score_data = json.load(f)
    f.close()
    bubble_sort(Score_data)
    Score_data = Score_data[:10]
    font.draw(300, 500, '[RANKING]', (100, 255, 100))
    y = 0
    for score in Score_data:
        font.draw(100, 450-40 *y, 'TIME:%3.3f, X:%3d, Y:%3d' %
                  (score['Time'],score['X'],score['Y']),
                  (255, 255, 255))
        y += 1

def draw(frame_time):
    global image
    clear_canvas()
    image.draw(400, 300)
    draw_rangking()
    update_canvas()



