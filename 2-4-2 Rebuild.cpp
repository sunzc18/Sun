#include<stdio.h>
using namespace std;
template<typename T>
class Stack//ջģ�嶨�壬ͬ�˹�����
{
private:
	int _top;
	int _size;
	T* stack;
public:
	Stack(int size)
	{
		_size = size;
		stack = new T[_size];
		_top=-1;
	}
	~Stack()
	{
		delete[] stack;
		stack = NULL;
	}
	void push(T i)
	{
		stack[++_top]=i;
	}
	T pop()
	{
		return stack[_top--];
	}
	bool empty()
	{
		return (_top==-1);
	}
	T top()
	{
		return stack[_top];
	}
};
template<typename T>
class Queue//˫ջ����
{
private:
	int _size;//˫ջ��С
	Stack<T>* out;//��ջ����
	Stack<T>* in;//��ջ����
public:
	Queue(int n):_size(n)//ջ���캯��
	{
		out = new Stack<T>(_size);
		in = new Stack<T>(_size);
	}
	void enqueue(T t)//�����
	{
		in->push(t);
	}
	T dequeue()//������
	{
		if(out->empty())//out��������in��Ԫ��ȫ��push��out��
		{
			while(!(in->empty()))
			{
				out->push(in->pop());
			}
		}
		return out->pop();
	}
	bool empty()//�������Ƿ�Ϊ��
	{
		return (in->empty())&&(out->empty());
	}
	~Queue()//��������
	{
		delete in;
		delete out;
		in = NULL;
		out = NULL;
	}
};
struct BinNode//�������ڵ㶨��
{
	int first_order;//������ĵ�һ�������е�λ��
	int second_order;//������ĵڶ��������е�λ��
	bool joined;//�Ƿ񱻼��������
	BinNode* parent;//���׽ڵ�
	BinNode* lc;//���ӽڵ�
	BinNode* rc;//�Һ��ӽڵ�
	int data;//�ýڵ�洢������
	BinNode()//���캯��
	{
		joined = false;
		parent = NULL;
		lc= NULL;
		rc=NULL;
	}
	void insertASLC(BinNode* leftchild)//��Ϊ���Ӳ���
	{
		lc = leftchild;
		leftchild->parent = this;
	}
	bool isRC()//�жϸýڵ��ǲ����Һ���
	{
		if(this->parent!=NULL)
		{
			return (this->parent->rc==this);
		}
		else
		{
			return true;
		}
	}
	bool isLC()//�жϸýڵ��ǲ�������
	{
		if(this->parent!=NULL)
		{
			return (this->parent->lc==this);
		}
		else
		{
			return true;
		}
	}
	void insertASRC(BinNode* rightchild)//��Ϊ�Һ��Ӳ���
	{
		rc = rightchild;
		rightchild->parent = this;
	}
	bool HasRChild()//�Ƿ�ӵ���Һ���
	{
		return !(rc==NULL);
	}
	bool HasLChild()//�Ƿ�ӵ������
	{
		return !(lc==NULL);
	}
};
class BinTree//������
{
private:
	BinNode** nodes;//�����洢1-n�ڵ��ָ��
	int* pre;//��һ�����������
	int* pos;//�ڶ������������
	int _size;//�����Ľڵ����
	BinNode* root;//���ڵ�
public:
	BinTree(){}//Ĭ�Ϲ��캯��
	BinTree(int size):_size(size)//���캯��
	{
		pre = new int[_size];
		pos = new int[_size];
		nodes = new BinNode*[_size];
		for(int i=0;i<_size;i++)
		{
			nodes[i] = new BinNode;
			nodes[i]->data = i+1;
		}//����n���ڵ�
		for(int i=0;i<_size;i++)
		{
			int s;
			scanf("%i",&s);
			pre[i] = s;
			nodes[s-1]->first_order = i;
		}//�����һ�����飬ͬʱ��¼�ڵ�nodes[s-1]��first_order
		for(int i=0;i<_size;i++)
		{
			int s;
			scanf("%i",&s);
			pos[i] = s;
			nodes[s-1]->second_order = i;
		}//����ڶ�������,ͬʱ��¼�ڵ�nodes[s-1]��second_order
	}
	void rebuild_1()//������Ϊ����������кͺ���������У��ұ�֤�ö�����Ϊ�������
	{
		Stack<BinNode*> trans(_size);//��תջ
		root = nodes[pre[0]-1];
		trans.push(root);//���ڵ���ջ
		BinNode* cursor;//ָʾ��ǰ�����ڵ�
		while(!trans.empty())//ջ�ǿ�
		{
			cursor = trans.pop();
			int lc = cursor->first_order+1;//������pre�б��
			int rc = cursor->second_order-1;//�Һ�����pos�б��
			if((lc<_size)&&(rc>=0))//�Ϸ��Լ��飬������Ϸ���ΪҶ�ڵ�
			{
				if((nodes[pre[lc]-1]->joined==false)&&(nodes[pos[rc]-1]->joined==false))//�Ϸ����Ҿ�δ����������
				{
					nodes[cursor->data-1]->insertASLC(nodes[pre[lc]-1]);
					nodes[cursor->data-1]->insertASRC(nodes[pos[rc]-1]);//�����ҽڵ����
					nodes[pre[lc]-1]->joined = true;
					nodes[pos[rc]-1]->joined = true;//���ı��
					trans.push(nodes[pre[lc]-1]);
					trans.push(nodes[pos[rc]-1]);//�����Һ�����ջ
				}
			}
		}
		travIn_I1(root);//�������
	}
	void rebuild_2()//������Ϊ����������������
	{
		Stack<BinNode*> trans(_size);//��תջ
		trans.push(root);//���ڵ���ջ
		for(int i=1;i<_size;i++)//�ӵڶ����ڵ㿪ʼ
		{
			BinNode* cursor = nodes[pre[i]-1];
			if(cursor->second_order<trans.top()->second_order)//��������ӣ��Ƚ����Ӽ���
			{
				trans.top()->insertASLC(cursor);//���Ӽ���
				trans.push(cursor);//������ջ
			}
			else//���������ͷ����Ϊ�ҽڵ����
			{
				while(cursor->parent==NULL)//��ǰ�����Ľڵ�δ�ҵ�����ʱ
				{
					if(!trans.top()->isRC())//���ջ��Ԫ��Ϊ����
					{
						BinNode* t = trans.pop();
						if(t->parent->second_order>cursor->second_order)//���ջ��Ԫ�ص�parent����������еĴ����cursor����cursor��Ϊt���Һ��ӣ���ʱt���Һ���ȷ����t��ջ��cursor��ջ
						{
							t->insertASRC(cursor);
							trans.push(cursor);
						}
					}
					else//���ջ��Ԫ��Ϊ�Һ��� 
					{
						BinNode* t = trans.pop();
						if(!trans.empty())//�������ջ��Ԫ�غ�ջ�ǿ�
						{
							if(trans.top()->second_order>cursor->second_order)//�жϵ�ǰ��������ĸ��ڵ���������������cursor��λ�ù�ϵ�����������������cursor��Ϊ����������
							{
								t->insertASRC(cursor);
								trans.push(cursor);
							}
						}
						else//ջ�գ��򵯳��ڵ�Ϊ���ڵ�
						{
							t->insertASRC(cursor);//��cursor���뼴��
							trans.push(cursor);
						}
					}
				}
			}

		}
		travPost_I(root);//��������������
	}
	void rebuild_3()//������������ͺ����������������͸�����������������������������ԭ������һ����ֻ�����ع������������ع����������������򣬲�������ж�����ȫ���෴���ѣ����ﲻ��׸��
	{
		Stack<BinNode*> trans(_size);
		root = nodes[pos[_size-1]-1];
		trans.push(root);
		for(int i=1;i<_size;i++)
		{
			BinNode* cursor = nodes[pos[_size-i-1]-1];
			if(cursor->first_order>trans.top()->first_order)
			{
				trans.top()->insertASRC(cursor);
				trans.push(cursor);
			}
			else
			{
				while(cursor->parent==NULL)
				{
					if(!trans.top()->isLC())
					{
						BinNode* t = trans.pop();
						if(t->parent->first_order<cursor->first_order)
						{
							t->insertASLC(cursor);
							trans.push(cursor);
						}
					}
					else 
					{
						BinNode* t = trans.pop();
						if(!trans.empty())
						{
							if(trans.top()->first_order<cursor->first_order)
							{
								t->insertASLC(cursor);
								trans.push(cursor);
							}
						}
						else
						{
							t->insertASLC(cursor);
							trans.push(cursor);
						}
					}
				}
			}
		}
		travPre_I1(root);
	}
	void rebuild_4()//������������ͺ�����������α�����Ψһ�������������ֻ��һ���ڵ���ô�޷��ж��ӽڵ��λ���������ң�����Բ�α�����û��Ӱ�죬�������ͳһ�����������룬ͬʱ������жϣ��������lc,rcָ��ͬһ��Ԫ�أ���ֻ����һ�μ���
	{
		Stack<BinNode*> trans(_size);
		root = nodes[pre[0]-1];
		trans.push(root);
		BinNode* cursor;
		while(!trans.empty())
		{
			cursor = trans.pop();
			int lc = cursor->first_order+1;
			int rc = cursor->second_order-1;
			if((lc<_size)&&(rc>=0))
			{
				if((nodes[pre[lc]-1]->joined==false)&&(nodes[pos[rc]-1]->joined==false))
				{
					if(pre[lc]!=pos[rc])//����жϣ�����ȷ���Ƿ�ֻ��һ���ڵ㣬���ǵĻ�����rebuild_1�н��в���
					{
						nodes[cursor->data-1]->insertASLC(nodes[pre[lc]-1]);
						nodes[cursor->data-1]->insertASRC(nodes[pos[rc]-1]);
						nodes[pre[lc]-1]->joined = true;
						nodes[pos[rc]-1]->joined = true;
						trans.push(nodes[pre[lc]-1]);
						trans.push(nodes[pos[rc]-1]);
					}
					else//�ǵĻ�����ڵ�ֻ����һ�μ���
					{
						nodes[cursor->data-1]->insertASLC(nodes[pre[lc]-1]);
						nodes[pre[lc]-1]->joined = true;
						trans.push(nodes[pre[lc]-1]);
					}
				}
			}
		}
		travLevel();//���в�α���
	}
	void goAlongVine(BinNode* x,Stack<BinNode*>& s)//ʵ�����������ͬ�˹�����
	{
		BinNode* t = x;
		while(t!=NULL)
		{
			s.push(t);
			t = t->lc;
		}
	}
	void travIn_I1(BinNode* x) 
	{
		Stack<BinNode*> s(_size);
		BinNode* t=x;
		while(true)
		{
			goAlongVine(t,s);
			if(s.empty()) break;
			t = s.pop();
			printf("%i ",t->data);
			t = t->rc;
		}
	}
	void travPre_I1(BinNode* x)//ʵ�����������ͬ�˹�����
	{
		Stack<BinNode*> S(_size);
		if(x) S.push(x);
		BinNode* cursor;
		while(!S.empty())
		{
			cursor = S.pop();
			printf("%i ",cursor->data);
			if(cursor->HasRChild())
			{
				S.push(cursor->rc);
			}
			if(cursor->HasLChild())
			{
				S.push(cursor->lc);
			}
		}
	}
	void gotoHLVFL(Stack<BinNode*>& S)//ʵ�ֺ��������ͬ�˹�����
	{
		while(BinNode* x = S.top())
		{
			if(x->HasLChild())
			{
				if(x->HasRChild())
				{
					S.push(x->rc);
				}
				S.push(x->lc);
			}
			else
			{
				S.push(x->rc);
			}
		}
		S.pop();
	}
	void travPost_I(BinNode* x)
	{
		Stack<BinNode*> S(1+_size);
		if(x)
		{
			S.push(x);
		}
		while(!S.empty())
		{
			if(S.top()!=x->parent)
			{
				gotoHLVFL(S);
			}
			x = S.pop();
			printf("%i ", x->data);
		}
	}
	void travLevel()//ʵ�ֲ�α�����ͬ�˹�����
	{
		Queue<BinNode*> Q(_size);
		Q.enqueue(root);
		while (!Q.empty())
		{
			BinNode* x = Q.dequeue();
			printf("%i ",x->data);
			if(x->HasLChild())
			{
				Q.enqueue(x->lc);
			}
			if(x->HasRChild())
			{
				Q.enqueue(x->rc);
			}
		}
	}
};
int main()
{
	int n,m;
	scanf("%i%i",&n,&m);//����n,m
	BinTree tree(n);//����������
	if(m==0)//����ĿҪ��ִ�в�ͬ�ĺ���
	{
		tree.rebuild_1();
	}
	else if(m==1)
	{
		tree.rebuild_2();
	}
	else if(m==2)
	{
		tree.rebuild_3();
	}
	else if(m==3)
	{
		tree.rebuild_4();
	}
	return 0;
}