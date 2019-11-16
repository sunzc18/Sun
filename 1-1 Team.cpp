#include<cstdio>
#include<string>
using namespace std;

int Team(int A[],int B[],int C[],bool N[],int& a,int& b,int& c,int& k,int K)//(其中A,B,C代表三个教练的喜欢程度表，N标记队员是否被选择，a,b,c记录当前遍历位置，k为计数变量，K为目标队员k)
{
	if(k%3==0)//(判断是哪一位教练选人)
	{
		int s=0;
		while(N[A[a+s]-1]==0)//判断该队员是否可用，不可用即跳过
		{
			s++;
		}
		N[A[a+s]-1] = 0;
		if(A[a+s] == K)
		{
			a = a+s+1;
			return 1;//1代表命中教练A
		}
		a =a+s+1;//改变游标a大小
	}
	else if(k%3 ==1)//(下面代码含义同上)
	{
		int s=0;
		while(N[B[b+s]-1]==0)
		{
			s++;
		}
		N[B[b+s]-1] = 0;
		if(B[b+s] == K)
		{
			b = b+s+1;
			return 2;
		}
		b=b+s+1;
	}
	else if(k%3 ==2)
	{
		int s=0;
		while(N[C[c+s]-1]==0)
		{
			s++;
		}
		N[C[c+s]-1] = 0;
		if(C[c+s] == K)
		{
			c = c+s+1;
			return 3;
		}
		c=c+s+1;
	}
	return 0;//返回值为0代表当前队员并不是k
}

int main()
{
	int n=0,k=0,m=0;
	int a = 0,b = 0,c = 0;
	scanf("%i",&n);
	int* A = new int[n];//分配内存空间
	int* B = new int[n];
	int* C = new int[n];
	bool* N = new bool[n];
	for(int i=0;i<n;i++)//初始化标记数组N
	{
		N[i]=1;
	}
	for(int i=0;i<n;i++)//初始化A
	{
		scanf("%i",&m);
		A[i]=m;
	}
	for(int i=0;i<n;i++)//初始化B
	{
		scanf("%i",&m);
		B[i]=m;
	}
	for(int i=0;i<n;i++)//初始化C
	{
		scanf("%i",&m);
		C[i]=m;
	}
	scanf("%i",&k);//输入k

	for(int i=0;i<n;i++)//为每位队员分配教练
	{
		int t = Team(A,B,C,N,a,b,c,i,k);//调用函数Team
		if(t!=0 )//判断是不是队员k
		{
			if(t == 1)
			{printf("%s","A");}
			else if(t==2)
			{printf("%s","B");}
			else if(t==3)
			{printf("%s","C");}
			break;//是队员k时结束循环
		}	
	}

	delete[] A;//释放内存空间
	delete[] B;
	delete[] C;
	delete[] N;
	return 0;
}