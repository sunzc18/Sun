#include<stdio.h>
using namespace std;
struct staff
{
	int id;
	staff* pred;//前驱指针
	staff* succ;//后继指针
	staff(){};
	staff(int id,staff* pred=NULL,staff* succ=NULL):id(id),pred(pred),succ(succ){};
};
class list
{
private:
	int _size;//列表大小
	staff* header;//header节点
	staff* trailer;//trailer节点
	staff* cursor;//游标，记录上一个操作的元素的地址
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
	void init(int i)//初始化，随机向列表中插入一个元素
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
	void normal_insert(int n,staff* p)//向p节点后插入一个节点
	{
		staff* N = new staff(n);
		N->succ = p->succ;
		p->succ->pred = N;
		N->pred = p;
		p->succ = N;
		_size++;
	}
	void traver()//反向遍历整个列表
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
	void insert(int k,int m)//按题目要求，间隔m个人插入
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
	list interview;//list类的实例化interview
	int n,m;
	scanf("%i%i",&n,&m);
	int s;
	scanf("%i",&s);
	interview.init(s);
	for(int i=1;i<n;i++)
	{
		scanf("%i",&s);
		interview.insert(s,m);//将对应元素插入
	}
	interview.traver();//反向遍历列表并输出
	return 0;
}