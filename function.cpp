#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
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

// 跳转到地图的位置，之后再改x轴和y轴
void gotoxy(int x,int y)
{
	COORD coord;
	coord.X = 2*x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// 错误报告
void error(string s){
	//在某个地方 log s
}
// 根据map的内容绘图
void print(vector <vector<int> > &map){
	gotoxy(0,0);
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WEIGHT; ++j) {
			if(map[i][j])	cout << "墙";
			else	cout << "  ";
			// switch(map[i][j]){
			// 	case 1: cout << "墙";break;
			// 	case 2: cout << "蛇";break;
			// 	case 3: cout << "头";break;
			// 	case 4: cout << "果";break;
			// 	default: cout << "  ";
			// }
		}
		cout << endl;
	}
}
//将map的值清空,初始化
void clear(vector <vector<int> > &map){
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WEIGHT; ++j) {
			if (i == 0 || i == HEIGHT - 1)	map[i][j] = 1;
			else if (j == 0 || j == WEIGHT - 1)	map[i][j] = 1;
			else map[i][j] = 0;
		}
	}
}

void draw_apple(vector <vector<int> > &map,vector <point> &apple){
    int sum = 0; // 空格子的个数
    int index = 0; // 剩下的格子
	point p;
    // 算出空格子的个数
    for(int i = 0; i < HEIGHT ; ++i){
        for(int j = 0; j < WEIGHT; ++j){
            if(map[i][j] == 0)
            {
                sum += 1;
            }
        }
    }
	srand((unsigned int)(clock()+time(NULL)));
    index = rand()%sum + 1; // 在1到sum 中随机的位置生成苹果
    //生成苹果
    for(int i = 0; i < HEIGHT; ++i){
        for(int j = 0; j < WEIGHT; ++j){
            if(map[i][j] == 0){
                index -= 1;
            }
            if(index == 0){
				map[i][j] = 4;
				p.set(i,j);
                apple.push_back(p);
				gotoxy(i,j);
				cout << "果";
				gotoxy(0, HEIGHT+1);
                return ;
            }
        }
    }
    return;
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
        switch (c){	
        case 'w': 	direction = 1;break;
        case 's':	direction = 2;break;
        case 'a':	direction = 3;break;
        case 'd': 	direction = 4;break;
        default:	break;
        }
    }
}
int snake::eat(vector <vector<int> > & map,vector <point> &apple){
	go(map);
	if(map[head.x][head.y] != 0){
		switch(map[head.x][head.y]){
			case 1: return 1;
			case 2: return 2;
			case 4: {
				map[head.x][head.y]=3;
				for(int i = 0; i<apple.size(); ++i){
					if(head.x == apple[i].x && head.y == apple[i].y){
						apple.erase(apple.begin()+i);
					}
				}
				return 4;
			}
		}
	}
	else{
		gotoxy(body[0].x,body[0].y);cout<<"  ";
		gotoxy(0, HEIGHT+1);
		map[body[0].x][body[0].y] = 0;
		body.pop_front();
		map[head.x][head.y]=3;
		return 0;
	}
	return -1;
}

// 判断方向前进
void snake::go(vector <vector<int> > & map){
	body.push_back(head);
	switch(direction){
		case 1: gotoxy(head.x,head.y);cout<<"蛇";map[head.x][head.y]=2;--head.y;gotoxy(head.x,head.y);cout<<"头";gotoxy(0, HEIGHT+1);break;
		case 2: gotoxy(head.x,head.y);cout<<"蛇";map[head.x][head.y]=2;++head.y;gotoxy(head.x,head.y);cout<<"头";gotoxy(0, HEIGHT+1);break;
		case 3: gotoxy(head.x,head.y);cout<<"蛇";map[head.x][head.y]=2;--head.x;gotoxy(head.x,head.y);cout<<"头";gotoxy(0, HEIGHT+1);break;
		case 4: gotoxy(head.x,head.y);cout<<"蛇";map[head.x][head.y]=2;++head.x;gotoxy(head.x,head.y);cout<<"头";gotoxy(0, HEIGHT+1);break;
		default: error("移动方向异常");
	}
}
// 将蛇的位置输出到map中，以便后续检测
void snake::draw(vector <vector<int> > & map){
		for(point p: body){
			map[p.x][p.y] = 2;
		}
		map[head.x][head.y] = 3;
}