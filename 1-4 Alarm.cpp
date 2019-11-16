#include<cstdio>
using namespace std;
struct point//point�ṹ��Ķ���
{
	long long int x,y;
	point(){}
	point(long long int x,long long int y):x(x),y(y){}
};
class line//line��Ķ���
{
private:
	long long int _x;//��������x����
	long long int _y;//��������y����
public:
	line(){}
	line(long long int _x,long long int _y):_x(_x),_y(_y){}//line��Ĺ��캯��
	int judge(point& p)//�жϵ���ֱ�ߵ�λ�ù�ϵ
	{
		long long int m =0;
		if(_x<0)//Ϊ�˴����������
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
	void init(int size)//��ʼ��line_set()
	{
		_size = size+1;
		Line = new line[_size];
		Line[0] = line(-1,-1);//��line(-1,-1)����Ϊ�˱���߽����
		long long int x,y;
		for(int i=1;i<_size;i++)//������������Line
		{
			scanf("%lli%lli",&x,&y);
			Line[i] = line(x,y);
		}
	}
	int alarm(point& p)//���ֲ��ң��ж�һ�������ڵ�λ��
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
	for(int i=0;i<m;i++)//����m����
	{
		long long int x,y;
		scanf("%lli%lli",&x,&y);
		P[i] = point(x,y);
	}
	for(int i=0;i<m;i++)//��m�����ö��ֲ����б���λ��
	{
		printf("%i\n",l.alarm(P[i]));
	}
	delete[] P;
	return 0;
}