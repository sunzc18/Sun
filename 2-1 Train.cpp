#include<stdio.h>
using namespace std;
class Train //Stack��
{
private:
	int top;//ջ�� top
	int N;//ջ���� N
	int* train;//�������������г�Ԫ��
public:
	Train(int n)//���캯��
	{
		N = n;
		top = -1;
		train = new int[N];
	}
	~Train()//�����������ͷſռ�
	{
		delete[] train;
		train = NULL;
	}
	void push(int n)//��ջ
	{
		train[++top] = n;
	}
	int pop()//��ջ
	{
			return(train[top--]);
	}
	bool full()//����Ƿ�ջ��
	{
		return(top==N-1);	
	}
	void init()//��ʼ����������������Ԫ��
	{
		int s;
		for(int i=0;i<N;i++)
		{
			scanf("%i",&s);
			train[N-i-1] = s;//����ֵ������ջ�����ԣ�ʹ���Ƚ��ȳ�
		}
		top = N-1;//��ʼ����ջ��
	}
	int Top()//�鿴����Ԫ��
	{
		return train[top];
	}
	bool empty()//����Ƿ�ջ��
	{
		return top==-1;
	}
	void line(int m)//������
	{
		init();
		Train trans(m);//��תջ
		int* num = new int[2*N];//�����洢ÿ���������г����
		char* op = new char[2*N+1];//�����洢ÿ������
		int s = 0;//�����洢Ŀǰ�����еĲ�������
		int k = 0;//�洢Ŀǰ�г��Ľ�չ���
		while(k!=N)//���г�û��ȫ��ʻ��ʱ
		{
			if((trans.Top()==k+1)&&(!trans.empty()))//��תջ�ǿ�����תջ��ǡ����Ӧ����ջ���г�
			{
				int t = trans.pop();//�������г�
				num[s] = t;
				op[s] = 'O';//��¼����
				s++;
				k++;
			}
			else
			{
				if(!empty())//�����������û�б�����
				{
					int t = pop();//�ӿ�ʼ��ջ����ջ��Ԫ��
					if(t==k+1)//�����Ԫ��ΪӦ��ʻ����г�
					{
						k++;//Ӧ��ʻ����г����++
						num[s] = t;//��¼����
						op[s] = 'P';
						s++;
					}
					else//�����ǰԪ�ز��ǽ�Ҫʻ�����г�
					{
						if(!trans.full())//����תջ����ʱ������ǰԪ������תջ
						{
							trans.push(t);
							num[s] = t;
							op[s] = 'I';//��¼����
							s++;
						}
						else//���ջ�����򲻿���
						{
							printf("No");
							return;
						}
					}
				}
				else//���ʻ���ջ�գ��򲻿���
				{
					printf("No");
					return;
				}
			}
		}
		for(int i =0;i<s;i++)//���ִ�е������������в���
		{
			printf("%i %c\n",num[i],op[i]);
		}
		delete[] num;//�ͷ��ڴ�
		delete[] op;//�ͷ��ڴ�
	}
};
int main()
{
	int n,m;
	scanf("%i%i",&n,&m);//����n.m
	Train train(n);//������СΪn��ջ
	train.line(m);//����line����
	return 0;
}

