#include <deque>
#include <vector>
using namespace std;

class point{
public:
	int x;
	int y;
	void set(int x, int y);
};

class snake{
private:
	int direction;
public:
	double speed;
	deque <point> body;
 	point head; 
	snake();
	void turn(char c);
	void go();
	void draw(vector <vector<int> > & map);
};
