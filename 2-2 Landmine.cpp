#include<stdio.h>
using namespace std;
int min(int x,int y)//将用于判断所得矩形的长宽大小是否符合题意
{
	if(x>y)
	{
		return y;
	}
	else
	{
		return x;
	}
}
class Stack//栈定义同邓公讲义，用于之后对矩形的每一列进行扫描
{
private:
	int _top;//栈顶
	int _N;//栈大小
	int* _stack;//栈指针
public:
	Stack(int n)//栈构造函数
	{
		_N=n;
		_top = -1;
		_stack = new int[_N];
	}
	~Stack()//析构函数
	{
		delete[] _stack;
		_stack=NULL;
	}
	void push(int s)//将s入栈
	{
		_stack[++_top] = s;
	}
	int pop()//将栈顶元素弹出
	{
		return _stack[_top--];
	}
	int top()//查看栈顶元素
	{
		return _stack[_top];
	}
	bool empty()//检查栈是否为空
	{
		return(_top==-1);
	}
};
class Landmine//landmine类
{
private:
	int n;//列数
	int m;//行数
	int** land;//二维数组指针用来存储输入的二维数组
public:
	Landmine(int n,int m):n(n),m(m){}//构造函数，指定landmine的列数和行数
	~Landmine()//析构函数释放内存
	{
		for(int i = 0;i<m;i++)
		{
			delete[] land[i];
		}
		delete[] land;
	}
	void init()//初始化函数，用来输入二维数组并对其进行预处理（将每一个元素变成其对应的行上右侧连续的可利用土地的数目）
	{
		land = new int*[m];//创建二维二维数组
		for(int i = 0;i<m;i++)
		{
			land[i] = new int[n];
			for(int j=0;j<n;j++)
			{
				int s ;
				scanf("%i",&s);//对二维数组中的元素赋值
				land[i][j] = s;
			}
		}
		for(int i=0;i<m;i++)//对二维数组中的元素每一行反向遍历，进行预处理
		{
			int t = 0;
			for(int j=0;j<n;j++)
			{
				if(land[i][n-j-1]!=0)
				{
					land[i][n-j-1] = ++t;
				}
				else
				{
					t = 0;
				}
			}
		}
	}
	void count(int n_max,int m_max)//计数函数，用来数出所有可能的矩形的个数
	{
		int Ans = 0;//用来存储当前已经发现的可能的矩形的数目
		Stack trans(m);//用来实现在一次遍历的过程中，数出该列所有可能的矩形数目
		int* mark = new int[m];//用来记录每个节点的前面有多少个比它大的节点
		for(int i = 0;i<n;i++)//遍历所有列
		{
			for(int j = 0;j<m;j++)//遍历所有行
			{
				if((!trans.empty()&&land[j][i]>=land[trans.top()][i])||trans.empty())//栈空或者当前元素比栈顶元素大
				{
					trans.push(j);//当前元素入栈
					mark[j] =0;//前面比它大的节点的数目为0，mark[j] = 0;
				}
				else if((!trans.empty())&&(land[j][i]<land[trans.top()][i]))//栈非空并且当前元素比栈顶元素小
				{
						int s = 1;//s记录当前已经出栈的元素的个数
						mark[j] = 0;//mark[j]初始化为0
						while((!trans.empty())&&(land[trans.top()][i]>land[j][i]))//栈非空并且栈顶元素比当前元素小
						{
							int k = trans.pop();//栈顶元素出栈，计算当前和它构成的所有的矩形
							if((mark[k]+s)<=m_max)//分类依据：当前可能的宽度是否大于m_max,如果不大于，那么就正常计算包含当前元素的所有元素的个数
							{
								Ans += (s*mark[k]+s)*min(land[k][i],n_max);
							}
							else//如果大于，按照下面利用等差数列求和计算得到的公式来计算所有符合条件的矩形个数
							{
								
								int a = min(s,m_max);
								int b = min(mark[k],m_max);
								Ans += ((m_max-a)*a+a+0.5*(m_max-b+a-1)*(-m_max+a+b))*min(land[k][i],n_max);
							}
							mark[j]+=1+mark[k];//更新mark[j]
							s +=mark[k]+1;//更新当前的深度s
						}
						trans.push(j);//将所有比j大的元素弹出后，j入栈
				}
			}
			int s = 1;
			while (!trans.empty())//当遍历结束后，栈内元素已经排成了有序序列，这时候再按上面的步骤将所有元素出栈并计算即可
			{
				int k = trans.pop();
				if((mark[k]+s)<=m_max)
				{
					Ans += (s*mark[k]+s)*min(land[k][i],n_max);
				}
				else
				{
					int a = min(s,m_max);
					int b = min(mark[k],m_max);
					Ans += ((m_max-a)*a+a+0.5*(m_max-b+a-1)*(-m_max+a+b))*min(land[k][i],n_max);
				}
				s += 1+mark[k];
			}
		}
		delete[] mark;//释放内存
		printf("%i",Ans%10007);//输出结果
	}
};                      
int main()
{
	int n,m;
	scanf("%i%i",&n,&m);//输入n,m
	int n_max,m_max;
	scanf("%i%i",&n_max,&m_max);//输入n_max,m_max
	Landmine landmine(n,m);
	landmine.init();//初始化landmine
	landmine.count(n_max,m_max);//计数
	return 0;
}