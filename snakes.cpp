#include "function.cpp"

using namespace std;

int main() {
	// 初始化
	system("chcp 65001");	//使终端支持UTF-8
	char ch;				//收集按键的变量
	clock_t start_time = clock();
	clock_t last_time = clock();
	vector <vector<int> > map(HEIGHT, vector<int> (WEIGHT));
	vector <point> apple;
	snake s;
	bool flag = true;		//判断游戏开始与结束
	int scroe = 0;			//游戏的分数

	clear(map); 			//初始化map
	print(map);				//绘制地图
	s.draw(map);			//将蛇的点注入map中
	

	while(flag){
		// kbhit()判断是否有按键
		if(kbhit()){
			ch = getch();		// getch()接收按键可以不在终端显示
		}
		clock_t time = clock();
		if(apple.size() < 10)	draw_apple(map,apple);	//使场上的苹果数为10
		//运行时间大于speed即移动
		if((double)(time - last_time)/CLOCKS_PER_SEC >= s.speed){
			last_time = time;
		  	s.turn(ch);
			// system("cls")是windows清屏的指令，如在linux使用clear
			switch(s.eat(map,apple)){
				case 1:	flag = false;system("cls");cout<<"你的分数是："<<scroe;break;
				case 2:	flag = false;system("cls");cout<<"你的分数是："<<scroe;break;
				case 4:	++scroe;break;	//迟到苹果加分
				default:break;
			}
		}
	}
	getchar();	//最后暂停一下，展示分数什么的，可以用其他函数代替
	return 0;
}