#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "class.hpp"
using namespace std;

#define	HEIGHT 20
#define WEIGHT 20

// 在linux下的代码， 要使用#include <termio.h>
// // 返回按下的键
// int getch(void)
// {
//     struct termios tm, tm_old;
//     int fd = 0, ch;
 
//     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
//         return -1;
//     }
 
//     tm_old = tm;
//     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
//     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
//         return -1;
//     }

//     ch = getchar();
//     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
//         return -1;
//     }

//     return ch;
// }
// // 判断是否有按键
// bool kbhit()
// {
//     termios term;
//     tcgetattr(0, &term);

//     termios term2 = term;
//     term2.c_lflag &= ~ICANON;
//     tcsetattr(0, TCSANOW, &term2);

//     int byteswaiting;
//     ioctl(0, FIONREAD, &byteswaiting);

//     tcsetattr(0, TCSANOW, &term);

//     return byteswaiting > 0;
// }

void error(string s){
	//在某个地方 log s
}
// 根据map的内容绘图
void print(vector <vector<int> > &map){
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WEIGHT; ++j) {
			switch(map[i][j]){
				case 1: cout << "墙";break;
				case 2: cout << "蛇";break;
				case 3: cout << "头";break;
				case 4: cout << "果";break;
				default: cout << "  ";
			}
		}
		cout << endl;
	}
}
//将map的值清空
void clear(vector <vector<int> > &map){
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WEIGHT; ++j) {
			if (i == 0 || i == HEIGHT - 1)	map[i][j] = 1;
			else if (j == 0 || j == WEIGHT - 1)	map[i][j] = 1;
			else map[i][j] = 0;
		}
	}
}

void point::set(int x, int y){
		this->x = x;
		this->y = y;
}
//初始化构建snake
snake::snake(){
		speed = 1.0;
		direction = 2;
		body.resize(2);
		body[0].set(2,2);
		body[1].set(3,2);
		head.set(4,2);
}
// 转方向
void snake::turn(char c){
    c = tolower(c);
    if(!((c == 'w' && direction == 2)||(c == 's' && direction == 1)||(c == 'a' && direction == 4)||(c == 'd' && direction == 3))){
        switch (c)
        {	
        case 'w': 	direction = 1;break;
        case 's':	direction = 2;break;
        case 'a':	direction = 3;break;
        case 'd': 	direction = 4;break;
        default:	break;
        }
    }
}
// 判断方向前进
void snake::go(){
		body.pop_front();
		body.push_back(head);
		switch(direction){
			case 1: --head.x;break;
			case 2: ++head.x;break;
			case 3: --head.y;break;
			case 4: ++head.y;break;
			default: error("移动方向异常");
		}
}
// 将蛇的位置输出到map中，以便打印  
void snake::draw(vector <vector<int> > & map){
		for(point p: body){
			map[p.x][p.y] = 2;
		}
		map[head.x][head.y] = 3;
}