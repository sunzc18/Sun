#include<stdio.h>
using namespace std;
class Bitmap//Bitmap�ඨ��
{
private:
	long long int* F;//�����洢ָ��
	long long int* T;//�����洢����
	long long int N;//Ա����Ŀ
	long long int top;//�洢��ǰ��½Ա����Ŀ�����ڿ���ʵ�ֳ�ʼ��
public:
	Bitmap(long long int n = 8)
	{
		top = 0;//top��ʼ��Ϊ0
		N = n;
		F = new long long int[N];//�洢ָ��
		T = new long long int[N];//�洢����
	}
	~Bitmap()//�����������ͷ��ڴ�
	{
		delete[] F;
		delete[] T;
	}
	bool test(long long int k )//����У�黷�жϣ������ж�Ա��k�Ƿ��½
	{
		return (F[k]>-1)&&(F[k]<top)&&(T[F[k]]==k);
	}
	void set(long long int k)//����У�黷
	{
		if(!test(k))
		{
			T[top] = k;
			F[k] = top;
			top++;
		}
	}
	void reset()//�߼��ϳ�ʼ����Bitmapʵ�ֿ��ٳ�ʼ��
	{
		top = 0;
	}
	void clear(long long int k)//ע���û�k
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
	long long int quiz()//��ѯ��ǰ����Ա������
	{
		return (top);
	}

};

int main()
{
	long long int n ,m;
	scanf("%lli%lli",&n,&m);//����n,m
	Bitmap staff(n);//����Bitmap�����staff
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