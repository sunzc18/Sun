#include<stdio.h>
using namespace std;
class Train //Stack类
{
private:
	int top;//栈顶 top
	int N;//栈容量 N
	int* train;//数组用来存入列车元素
public:
	Train(int n)//构造函数
	{
		N = n;
		top = -1;
		train = new int[N];
	}
	~Train()//析构函数，释放空间
	{
		delete[] train;
		train = NULL;
	}
	void push(int n)//入栈
	{
		train[++top] = n;
	}
	int pop()//出栈
	{
			return(train[top--]);
	}
	bool full()//检查是否栈满
	{
		return(top==N-1);	
	}
	void init()//初始化函数，输入数组元素
	{
		int s;
		for(int i=0;i<N;i++)
		{
			scanf("%i",&s);
			train[N-i-1] = s;//倒序赋值，根据栈的特性，使其先进先出
		}
		top = N-1;//初始设置栈满
	}
	int Top()//查看顶部元素
	{
		return train[top];
	}
	bool empty()//检查是否栈空
	{
		return top==-1;
	}
	void line(int m)//排序函数
	{
		init();
		Train trans(m);//中转栈
		int* num = new int[2*N];//用来存储每步操作的列车编号
		char* op = new char[2*N+1];//用来存储每步操作
		int s = 0;//用来存储目前所进行的操作步数
		int k = 0;//存储目前列车的进展情况
		while(k!=N)//当列车没有全部驶过时
		{
			if((trans.Top()==k+1)&&(!trans.empty()))//中转栈非空且中转栈顶恰好是应该入栈的列车
			{
				int t = trans.pop();//弹出该列车
				num[s] = t;
				op[s] = 'O';//记录操作
				s++;
				k++;
			}
			else
			{
				if(!empty())//当输入的序列没有遍历完
				{
					int t = pop();//从开始的栈弹出栈顶元素
					if(t==k+1)//如果该元素为应该驶入的列车
					{
						k++;//应该驶入的列车编号++
						num[s] = t;//记录操作
						op[s] = 'P';
						s++;
					}
					else//如果当前元素不是将要驶过的列车
					{
						if(!trans.full())//当中转栈非满时，将当前元素入中转栈
						{
							trans.push(t);
							num[s] = t;
							op[s] = 'I';//记录操作
							s++;
						}
						else//如果栈满，则不可以
						{
							printf("No");
							return;
						}
					}
				}
				else//如果驶入的栈空，则不可以
				{
					printf("No");
					return;
				}
			}
		}
		for(int i =0;i<s;i++)//如果执行到最后，则输出所有操作
		{
			printf("%i %c\n",num[i],op[i]);
		}
		delete[] num;//释放内存
		delete[] op;//释放内存
	}
};
int main()
{
	int n,m;
	scanf("%i%i",&n,&m);//输入n.m
	Train train(n);//创建大小为n的栈
	train.line(m);//调用line函数
	return 0;
}

