#include<stdio.h>
using namespace std;
int min(int x,int y)//�������ж����þ��εĳ����С�Ƿ��������
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
class Stack//ջ����ͬ�˹����壬����֮��Ծ��ε�ÿһ�н���ɨ��
{
private:
	int _top;//ջ��
	int _N;//ջ��С
	int* _stack;//ջָ��
public:
	Stack(int n)//ջ���캯��
	{
		_N=n;
		_top = -1;
		_stack = new int[_N];
	}
	~Stack()//��������
	{
		delete[] _stack;
		_stack=NULL;
	}
	void push(int s)//��s��ջ
	{
		_stack[++_top] = s;
	}
	int pop()//��ջ��Ԫ�ص���
	{
		return _stack[_top--];
	}
	int top()//�鿴ջ��Ԫ��
	{
		return _stack[_top];
	}
	bool empty()//���ջ�Ƿ�Ϊ��
	{
		return(_top==-1);
	}
};
class Landmine//landmine��
{
private:
	int n;//����
	int m;//����
	int** land;//��ά����ָ�������洢����Ķ�ά����
public:
	Landmine(int n,int m):n(n),m(m){}//���캯����ָ��landmine������������
	~Landmine()//���������ͷ��ڴ�
	{
		for(int i = 0;i<m;i++)
		{
			delete[] land[i];
		}
		delete[] land;
	}
	void init()//��ʼ�����������������ά���鲢�������Ԥ������ÿһ��Ԫ�ر�����Ӧ�������Ҳ������Ŀ��������ص���Ŀ��
	{
		land = new int*[m];//������ά��ά����
		for(int i = 0;i<m;i++)
		{
			land[i] = new int[n];
			for(int j=0;j<n;j++)
			{
				int s ;
				scanf("%i",&s);//�Զ�ά�����е�Ԫ�ظ�ֵ
				land[i][j] = s;
			}
		}
		for(int i=0;i<m;i++)//�Զ�ά�����е�Ԫ��ÿһ�з������������Ԥ����
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
	void count(int n_max,int m_max)//���������������������п��ܵľ��εĸ���
	{
		int Ans = 0;//�����洢��ǰ�Ѿ����ֵĿ��ܵľ��ε���Ŀ
		Stack trans(m);//����ʵ����һ�α����Ĺ����У������������п��ܵľ�����Ŀ
		int* mark = new int[m];//������¼ÿ���ڵ��ǰ���ж��ٸ�������Ľڵ�
		for(int i = 0;i<n;i++)//����������
		{
			for(int j = 0;j<m;j++)//����������
			{
				if((!trans.empty()&&land[j][i]>=land[trans.top()][i])||trans.empty())//ջ�ջ��ߵ�ǰԪ�ر�ջ��Ԫ�ش�
				{
					trans.push(j);//��ǰԪ����ջ
					mark[j] =0;//ǰ�������Ľڵ����ĿΪ0��mark[j] = 0;
				}
				else if((!trans.empty())&&(land[j][i]<land[trans.top()][i]))//ջ�ǿղ��ҵ�ǰԪ�ر�ջ��Ԫ��С
				{
						int s = 1;//s��¼��ǰ�Ѿ���ջ��Ԫ�صĸ���
						mark[j] = 0;//mark[j]��ʼ��Ϊ0
						while((!trans.empty())&&(land[trans.top()][i]>land[j][i]))//ջ�ǿղ���ջ��Ԫ�رȵ�ǰԪ��С
						{
							int k = trans.pop();//ջ��Ԫ�س�ջ�����㵱ǰ�������ɵ����еľ���
							if((mark[k]+s)<=m_max)//�������ݣ���ǰ���ܵĿ���Ƿ����m_max,��������ڣ���ô���������������ǰԪ�ص�����Ԫ�صĸ���
							{
								Ans += (s*mark[k]+s)*min(land[k][i],n_max);
							}
							else//������ڣ������������õȲ�������ͼ���õ��Ĺ�ʽ���������з��������ľ��θ���
							{
								
								int a = min(s,m_max);
								int b = min(mark[k],m_max);
								Ans += ((m_max-a)*a+a+0.5*(m_max-b+a-1)*(-m_max+a+b))*min(land[k][i],n_max);
							}
							mark[j]+=1+mark[k];//����mark[j]
							s +=mark[k]+1;//���µ�ǰ�����s
						}
						trans.push(j);//�����б�j���Ԫ�ص�����j��ջ
				}
			}
			int s = 1;
			while (!trans.empty())//������������ջ��Ԫ���Ѿ��ų����������У���ʱ���ٰ�����Ĳ��轫����Ԫ�س�ջ�����㼴��
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
		delete[] mark;//�ͷ��ڴ�
		printf("%i",Ans%10007);//������
	}
};                      
int main()
{
	int n,m;
	scanf("%i%i",&n,&m);//����n,m
	int n_max,m_max;
	scanf("%i%i",&n_max,&m_max);//����n_max,m_max
	Landmine landmine(n,m);
	landmine.init();//��ʼ��landmine
	landmine.count(n_max,m_max);//����
	return 0;
}