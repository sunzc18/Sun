#include<stdio.h>
using namespace std;
class Bitmap//Bitmap类定义
{
private:
	long long int* F;//用来存储指针
	long long int* T;//用来存储数据
	long long int N;//员工数目
	long long int top;//存储当前登陆员工数目，便于快速实现初始化
public:
	Bitmap(long long int n = 8)
	{
		top = 0;//top初始化为0
		N = n;
		F = new long long int[N];//存储指针
		T = new long long int[N];//存储数据
	}
	~Bitmap()//析构函数，释放内存
	{
		delete[] F;
		delete[] T;
	}
	bool test(long long int k )//利用校验环判断，用来判断员工k是否登陆
	{
		return (F[k]>-1)&&(F[k]<top)&&(T[F[k]]==k);
	}
	void set(long long int k)//构建校验环
	{
		if(!test(k))
		{
			T[top] = k;
			F[k] = top;
			top++;
		}
	}
	void reset()//逻辑上初始化，Bitmap实现快速初始化
	{
		top = 0;
	}
	void clear(long long int k)//注销用户k
	{
		if(test(k))
		{
			if(--top)
			{
				F[T[top]] = F[k];
				T[F[k]] = T[top];
			}
		}
	}
	long long int quiz()//查询当前工作员工个数
	{
		return (top);
	}

};

int main()
{
	long long int n ,m;
	scanf("%lli%lli",&n,&m);//输入n,m
	Bitmap staff(n);//构建Bitmap类对象staff
	char C;
	long long int a=-1,c=-1;
	long long int* code = new long long int[n];
	long long int Ans =0;
	for(int i=0;i<m;i++)
	{

		scanf("%c",&C);
		if(int(C)==10)
		{
			i--;
		}
		else if(C=='I')
		{
			scanf("%lli%lli",&a,&c);
			staff.set(a-1);
			code[a-1] = c;
		}
		else if(C=='O')
		{
			scanf("%lli",&a);
			staff.clear(a-1);
		}
		else if(C=='C')
		{
			staff.reset();
		}
		else if(C=='N')
		{
			Ans += staff.quiz();
		}
		else if(C=='Q')
		{
			scanf("%lli",&a);
			if(staff.test(a-1))
			{
				Ans += code[a-1];
			}
			else
			{
				Ans=Ans-1;
			}
		}
	}
	printf("%lli",Ans);
	return 0;
}