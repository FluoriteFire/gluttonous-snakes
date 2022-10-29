#include "function.cpp"

using namespace std;

int main() {
	// 初始化
	system("chcp 65001");
	char ch;
	clock_t start_time = clock();
	clock_t last_time = clock();
	vector <vector<int> > map(HEIGHT, vector<int> (WEIGHT));
	vector <point> apple;
	snake s;
	bool flag = true;
	int scroe = 0;

	clear(map); 
	print(map);
	s.draw(map);
	

	while(flag){
		if(kbhit()){
			ch = getch();
		}
		clock_t time = clock();
		if(apple.size() < 10)	draw_apple(map,apple);
		if((double)(time - last_time)/CLOCKS_PER_SEC >= s.speed){
			last_time = time;
		  	s.turn(ch);
			switch(s.eat(map,apple)){
				case 1:	flag = false;system("cls");cout<<"你的分数是："<<scroe;break;
				case 2:	flag = false;system("cls");cout<<"你的分数是："<<scroe;break;
				case 4:	++scroe;break;
				default:break;
			}
		}
	}
	getchar();
	return 0;
}