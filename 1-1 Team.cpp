#include<cstdio>
#include<string>
using namespace std;

int Team(int A[],int B[],int C[],bool N[],int& a,int& b,int& c,int& k,int K)//(����A,B,C��������������ϲ���̶ȱ�N��Ƕ�Ա�Ƿ�ѡ��a,b,c��¼��ǰ����λ�ã�kΪ����������KΪĿ���Աk)
{
	if(k%3==0)//(�ж�����һλ����ѡ��)
	{
		int s=0;
		while(N[A[a+s]-1]==0)//�жϸö�Ա�Ƿ���ã������ü�����
		{
			s++;
		}
		N[A[a+s]-1] = 0;
		if(A[a+s] == K)
		{
			a = a+s+1;
			return 1;//1�������н���A
		}
		a =a+s+1;//�ı��α�a��С
	}
	else if(k%3 ==1)//(������뺬��ͬ��)
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
	return 0;//����ֵΪ0����ǰ��Ա������k
}

int main()
{
	int n=0,k=0,m=0;
	int a = 0,b = 0,c = 0;
	scanf("%i",&n);
	int* A = new int[n];//�����ڴ�ռ�
	int* B = new int[n];
	int* C = new int[n];
	bool* N = new bool[n];
	for(int i=0;i<n;i++)//��ʼ���������N
	{
		N[i]=1;
	}
	for(int i=0;i<n;i++)//��ʼ��A
	{
		scanf("%i",&m);
		A[i]=m;
	}
	for(int i=0;i<n;i++)//��ʼ��B
	{
		scanf("%i",&m);
		B[i]=m;
	}
	for(int i=0;i<n;i++)//��ʼ��C
	{
		scanf("%i",&m);
		C[i]=m;
	}
	scanf("%i",&k);//����k

	for(int i=0;i<n;i++)//Ϊÿλ��Ա�������
	{
		int t = Team(A,B,C,N,a,b,c,i,k);//���ú���Team
		if(t!=0 )//�ж��ǲ��Ƕ�Աk
		{
			if(t == 1)
			{printf("%s","A");}
			else if(t==2)
			{printf("%s","B");}
			else if(t==3)
			{printf("%s","C");}
			break;//�Ƕ�Աkʱ����ѭ��
		}	
	}

	delete[] A;//�ͷ��ڴ�ռ�
	delete[] B;
	delete[] C;
	delete[] N;
	return 0;
}