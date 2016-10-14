from pico2d import *

def handle_events():
    global running
    global x
    global y
    global r
    global pivotx
    global pivoty
    events = get_events()
    for event in events:
        if event.type == SDL_QUIT:
            running = False
        elif event.type == SDL_MOUSEMOTION:
            pivotx, pivoty = event.x, 600 - event.y
        elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
            running = False
        elif event.type == SDL_KEYDOWN:
            if event.key == SDLK_RIGHT:
                pivotx += 10
            elif event.key == SDLK_LEFT:
                pivotx -= 10
            elif event.key == SDLK_DOWN:
                pivoty -= 10
            elif event.key == SDLK_UP:
                pivoty += 10
            elif event.key == SDLK_a:
                if r < 300 :
                     r += 50;
            elif event.key == SDLK_d:
                if 20 < r:
                    r -= 50;


    # fill here



open_canvas()
grass = load_image('grass.png')
character = load_image('run_animation.png')

running = True
x = 300
y = 300
r = 100
pivotx = 400
pivoty = 300
frame = 0
while (running):
    clear_canvas()
    grass.draw(400, 30)
    character.clip_draw(frame * 100, 0, 100, 100, r* math.cos(x) + pivotx, r* math.sin(x) + pivoty)
    update_canvas()
    frame = (frame + 1) % 8

    delay(0.1)
    handle_events()

    x += 1
    y += 1

close_canvas()

