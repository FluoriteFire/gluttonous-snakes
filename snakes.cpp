#include <time.h>
#include "function.cpp"

using namespace std;

int main() {
	// 初始化
	system("chcp 65001");
	char ch;
	clock_t start_time = clock();
	clock_t last_time = clock();
	vector <vector<int> > map(HEIGHT, vector<int> (WEIGHT));
	snake s;

	while(1){
		if(kbhit()){
			ch = getch();
		}
		clock_t time = clock();
		if((double)(time - last_time)/CLOCKS_PER_SEC >= s.speed){
			last_time = time;
		  	s.turn(ch);
			s.go(); 
			clear(map); 
			s.draw(map);
    		system("cls");	//linux 使用 clear
			print(map);
		}
	}
	return 0;
}