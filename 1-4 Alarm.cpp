#include<cstdio>
using namespace std;
struct point//point结构体的定义
{
	long long int x,y;
	point(){}
	point(long long int x,long long int y):x(x),y(y){}
};
class line//line类的定义
{
private:
	long long int _x;//题中所给x坐标
	long long int _y;//题中所给y坐标
public:
	line(){}
	line(long long int _x,long long int _y):_x(_x),_y(_y){}//line类的构造函数
	int judge(point& p)//判断点与直线的位置关系
	{
		long long int m =0;
		if(_x<0)//为了处理特例情况
		{
			m =-1*((p.x-_x)*_y+p.y*_x);
		}
		else
		{
			m = ((p.x-_x)*_y+p.y*_x);
		}
		if(m>0)
		{
			return 1;
		}
		else if(m==0)
		{
			return 0;
		}
		else if(m<0)
		{
			return -1;
		}
	}
};
class line_set
{
private:
	int _size;
	line* Line;
public:
	line_set(){}
	void init(int size)//初始化line_set()
	{
		_size = size+1;
		Line = new line[_size];
		Line[0] = line(-1,-1);//将line(-1,-1)插入为了避免边界情况
		long long int x,y;
		for(int i=1;i<_size;i++)//将插入其他的Line
		{
			scanf("%lli%lli",&x,&y);
			Line[i] = line(x,y);
		}
	}
	int alarm(point& p)//二分查找，判断一个点所在的位置
	{
		int lo = 0;
		int hi = _size;
		while(hi-lo!=1)
		{
			int mi = (lo+hi)/2;
			int t = Line[mi].judge(p);
			if(t==1)
			{
				lo = mi;
			}
			else if(t==-1)
			{
				hi = mi;
			}
			else if(t==0)
			{
				return mi;
			}
		}
		return lo;
	}
	~line_set()
	{
		delete[] Line;
		Line = NULL;
	}
};
int main()
{
	int n,m;
	scanf("%i%i",&n,&m);
	line_set l;
	l.init(n);
	point* P = new point[m];
	for(int i=0;i<m;i++)//输入m个点
	{
		long long int x,y;
		scanf("%lli%lli",&x,&y);
		P[i] = point(x,y);
	}
	for(int i=0;i<m;i++)//对m个点用二分查找判别其位置
	{
		printf("%i\n",l.alarm(P[i]));
	}
	delete[] P;
	return 0;
}