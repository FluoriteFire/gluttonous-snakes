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
	clear(map); 
	print(map);
	s.draw(map);
	

	while(1){
		if(kbhit()){
			ch = getch();
		}
		clock_t time = clock();
		if(apple.size() < 10)	draw_apple(map,apple);
		if((double)(time - last_time)/CLOCKS_PER_SEC >= s.speed){
			last_time = time;
		  	s.turn(ch);
			s.eat(map,apple); 
		}
	}
	return 0;
}