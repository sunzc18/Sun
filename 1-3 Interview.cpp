#include<stdio.h>
using namespace std;
struct staff
{
	int id;
	staff* pred;//ǰ��ָ��
	staff* succ;//���ָ��
	staff(){};
	staff(int id,staff* pred=NULL,staff* succ=NULL):id(id),pred(pred),succ(succ){};
};
class list
{
private:
	int _size;//�б��С
	staff* header;//header�ڵ�
	staff* trailer;//trailer�ڵ�
	staff* cursor;//�α꣬��¼��һ��������Ԫ�صĵ�ַ
public:
	list(){}
	~list()
	{
		staff* t = header->succ;
		while(t!=trailer)
		{
			staff* N = t->succ;
			delete t;
			t = N;
		}
		delete header;
		delete trailer;
		header = NULL;
		trailer = NULL;
	}
	void init(int i)//��ʼ����������б��в���һ��Ԫ��
	{
		header = new staff;
		trailer = new staff;
		cursor = new staff(i);
		cursor->pred = header;
		cursor->succ = trailer;
		header->pred = NULL;
		header->succ = cursor;
		trailer->succ = NULL;
		trailer->pred = cursor;
		_size=1;
	}
	void normal_insert(int n,staff* p)//��p�ڵ�����һ���ڵ�
	{
		staff* N = new staff(n);
		N->succ = p->succ;
		p->succ->pred = N;
		N->pred = p;
		p->succ = N;
		_size++;
	}
	void traver()//������������б�
	{
		int i = 0;
		staff* iter = cursor; 
		while(i!=_size)
		{
			if (iter->pred!=header)
			{
				printf("%i ",iter->id);
				iter = iter->pred;
			}
			else
			{
				printf("%i ",iter->id);
				iter = trailer->pred;
			}
			i++;
		}
	}
	void insert(int k,int m)//����ĿҪ�󣬼��m���˲���
	{
		staff* iter = cursor;
		for(int i=1;i<m;i++)
		{
			if(iter->succ !=trailer)
			{
				iter = iter->succ;
			}
			else
			{
				iter = header->succ;
			}
		}
		normal_insert(k,iter);
		cursor = iter->succ;
	}
};
int main()
{
	list interview;//list���ʵ����interview
	int n,m;
	scanf("%i%i",&n,&m);
	int s;
	scanf("%i",&s);
	interview.init(s);
	for(int i=1;i<n;i++)
	{
		scanf("%i",&s);
		interview.insert(s,m);//����ӦԪ�ز���
	}
	interview.traver();//��������б����
	return 0;
}