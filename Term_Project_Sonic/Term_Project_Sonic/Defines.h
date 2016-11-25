#include <gl/glut.h>
#include <time.h>
#include <iostream>// 헤더 파일
using namespace std;
// 필요한 전역 변수 선언


void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void Reshape(int w, int h);
void DrawScene();
void SetupRC();
void Mouse(int button, int state, int x, int y); 
