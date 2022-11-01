#include <deque>
#include <vector>
using namespace std;

// 类型point，（x,y)坐标
class point{
public:
	int x;
	int y;
	void set(int x, int y); // 设置point的x和y值
};

// 类型蛇，使用双端队列deque的设计
class snake{
private:
	int direction;	//蛇前进的方向，使用turn函数改变
public:
	double speed;	//蛇移动速度，设为pubilc方便调用和访问
	deque <point> body;	//蛇的身体
 	point head; 	//蛇的头部
	snake();		//初始化函数
	void turn(char c);	//转向
	void go(vector <vector<int> > & map);	//前进
	void draw(vector <vector<int> > & map);	//将蛇的点添加到map中，可以优化
	int eat(vector <vector<int> > & map,vector <point> &apple);	//蛇的碰撞检测
};
