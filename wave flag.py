from pico2d import *
open_canvas()
#grass = load_image('grass.png')
character = load_image('run_animation.png')
wave = load_image('wave animation2 copy.png')

background1= load_image('Base BackGround1.png')
background2= load_image('Base BackGround2.png')
background3= load_image('Base BackGround3.png')
Background = load_image('Background.png')
bluewave = load_image('blue-wave.png')
headerwave = load_image('header_waves.png')

x = 100
frame = 0
while (x < 800):

    clear_canvas()
    Background.draw(400 ,300)
    wave.clip_draw(frame * 400, 20, 235, 300, 80, 330)
   # bluewave.clip_draw(frame * 400, 20, 235, 300, x, 0)
    #headerwave.clip_draw(frame* 400 ,40, 600, 100 , 300,200)
    update_canvas()
    frame = (frame + 1) % 4
    # 특정한 정수를 반복할때. 나머지 연산
    # if문 보다 이해하기 편함.
    # x += 15
    delay(0.17)
    get_events()



# 여기를 채우세요.


