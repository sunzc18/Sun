#include<stdio.h>
using namespace std;
template<typename T>
class Stack//栈模板定义，同邓公讲义
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
class Queue//双栈当队
{
private:
	int _size;//双栈大小
	Stack<T>* out;//出栈数组
	Stack<T>* in;//入栈数组
public:
	Queue(int n):_size(n)//栈构造函数
	{
		out = new Stack<T>(_size);
		in = new Stack<T>(_size);
	}
	void enqueue(T t)//入队列
	{
		in->push(t);
	}
	T dequeue()//出队列
	{
		if(out->empty())//out空则将所有in中元素全部push入out中
		{
			while(!(in->empty()))
			{
				out->push(in->pop());
			}
		}
		return out->pop();
	}
	bool empty()//检查队列是否为空
	{
		return (in->empty())&&(out->empty());
	}
	~Queue()//析构函数
	{
		delete in;
		delete out;
		in = NULL;
		out = NULL;
	}
};
struct BinNode//二叉树节点定义
{
	int first_order;//在输入的第一个数组中的位置
	int second_order;//在输入的第二个数组中的位置
	bool joined;//是否被加入二叉树
	BinNode* parent;//父亲节点
	BinNode* lc;//左孩子节点
	BinNode* rc;//右孩子节点
	int data;//该节点存储的数据
	BinNode()//构造函数
	{
		joined = false;
		parent = NULL;
		lc= NULL;
		rc=NULL;
	}
	void insertASLC(BinNode* leftchild)//作为左孩子插入
	{
		lc = leftchild;
		leftchild->parent = this;
	}
	bool isRC()//判断该节点是不是右孩子
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
	bool isLC()//判断该节点是不是左孩子
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
	void insertASRC(BinNode* rightchild)//作为右孩子插入
	{
		rc = rightchild;
		rightchild->parent = this;
	}
	bool HasRChild()//是否拥有右孩子
	{
		return !(rc==NULL);
	}
	bool HasLChild()//是否拥有左孩子
	{
		return !(lc==NULL);
	}
};
class BinTree//二叉树
{
private:
	BinNode** nodes;//用来存储1-n节点的指针
	int* pre;//第一个输入的数组
	int* pos;//第二个输入的数组
	int _size;//该树的节点个数
	BinNode* root;//根节点
public:
	BinTree(){}//默认构造函数
	BinTree(int size):_size(size)//构造函数
	{
		pre = new int[_size];
		pos = new int[_size];
		nodes = new BinNode*[_size];
		for(int i=0;i<_size;i++)
		{
			nodes[i] = new BinNode;
			nodes[i]->data = i+1;
		}//生成n个节点
		for(int i=0;i<_size;i++)
		{
			int s;
			scanf("%i",&s);
			pre[i] = s;
			nodes[s-1]->first_order = i;
		}//输入第一个数组，同时记录节点nodes[s-1]的first_order
		for(int i=0;i<_size;i++)
		{
			int s;
			scanf("%i",&s);
			pos[i] = s;
			nodes[s-1]->second_order = i;
		}//输入第二个数组,同时记录节点nodes[s-1]的second_order
	}
	void rebuild_1()//当输入为先序遍历序列和后序遍历序列，且保证该二叉树为真二叉树
	{
		Stack<BinNode*> trans(_size);//中转栈
		root = nodes[pre[0]-1];
		trans.push(root);//根节点入栈
		BinNode* cursor;//指示当前操作节点
		while(!trans.empty())//栈非空
		{
			cursor = trans.pop();
			int lc = cursor->first_order+1;//左孩子在pre中编号
			int rc = cursor->second_order-1;//右孩子在pos中编号
			if((lc<_size)&&(rc>=0))//合法性检验，如果不合法即为叶节点
			{
				if((nodes[pre[lc]-1]->joined==false)&&(nodes[pos[rc]-1]->joined==false))//合法并且均未被加入子树
				{
					nodes[cursor->data-1]->insertASLC(nodes[pre[lc]-1]);
					nodes[cursor->data-1]->insertASRC(nodes[pos[rc]-1]);//将左右节点插入
					nodes[pre[lc]-1]->joined = true;
					nodes[pos[rc]-1]->joined = true;//更改标记
					trans.push(nodes[pre[lc]-1]);
					trans.push(nodes[pos[rc]-1]);//将左右孩子入栈
				}
			}
		}
		travIn_I1(root);//中序遍历
	}
	void rebuild_2()//当输入为先序遍历和中序遍历
	{
		Stack<BinNode*> trans(_size);//中转栈
		trans.push(root);//根节点入栈
		for(int i=1;i<_size;i++)//从第二个节点开始
		{
			BinNode* cursor = nodes[pre[i]-1];
			if(cursor->second_order<trans.top()->second_order)//如果有左孩子，先将左孩子加入
			{
				trans.top()->insertASLC(cursor);//左孩子加入
				trans.push(cursor);//左孩子入栈
			}
			else//否则遍历到头，作为右节点插入
			{
				while(cursor->parent==NULL)//当前操作的节点未找到父亲时
				{
					if(!trans.top()->isRC())//如果栈顶元素为左孩子
					{
						BinNode* t = trans.pop();
						if(t->parent->second_order>cursor->second_order)//如果栈顶元素的parent在中序遍历中的次序比cursor大，则cursor必为t的右孩子，此时t左右孩子确定，t出栈，cursor入栈
						{
							t->insertASRC(cursor);
							trans.push(cursor);
						}
					}
					else//如果栈顶元素为右孩子 
					{
						BinNode* t = trans.pop();
						if(!trans.empty())//如果弹出栈顶元素后，栈非空
						{
							if(trans.top()->second_order>cursor->second_order)//判断当前这颗子树的根节点的中序遍历次序与cursor的位置关系，如果满足条件，则将cursor作为右子树插入
							{
								t->insertASRC(cursor);
								trans.push(cursor);
							}
						}
						else//栈空，则弹出节点为根节点
						{
							t->insertASRC(cursor);//将cursor插入即可
							trans.push(cursor);
						}
					}
				}
			}

		}
		travPost_I(root);//后续遍历二叉树
	}
	void rebuild_3()//给出中序遍历和后序遍历求先序遍历和给出先序遍历和中序遍历求后序遍历的原理本质上一样，只是先重构右子树，再重构左子树，遍历次序，插入次序，判断依据全部相反而已，这里不再赘述
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
	void rebuild_4()//给出先序遍历和后序遍历，求层次遍历的唯一问题是如果子树只有一个节点那么无法判断子节点的位置是左还是右，但这对层次遍历并没有影响，因此这里统一按左子树插入，同时，添加判断，如果两个lc,rc指向同一个元素，则只插入一次即可
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
					if(pre[lc]!=pos[rc])//添加判断，用来确认是否只有一个节点，不是的话，按rebuild_1中进行操作
					{
						nodes[cursor->data-1]->insertASLC(nodes[pre[lc]-1]);
						nodes[cursor->data-1]->insertASRC(nodes[pos[rc]-1]);
						nodes[pre[lc]-1]->joined = true;
						nodes[pos[rc]-1]->joined = true;
						trans.push(nodes[pre[lc]-1]);
						trans.push(nodes[pos[rc]-1]);
					}
					else//是的话按左节点只插入一次即可
					{
						nodes[cursor->data-1]->insertASLC(nodes[pre[lc]-1]);
						nodes[pre[lc]-1]->joined = true;
						trans.push(nodes[pre[lc]-1]);
					}
				}
			}
		}
		travLevel();//进行层次遍历
	}
	void goAlongVine(BinNode* x,Stack<BinNode*>& s)//实现中序遍历，同邓公讲义
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
	void travPre_I1(BinNode* x)//实现先序遍历，同邓公讲义
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
	void gotoHLVFL(Stack<BinNode*>& S)//实现后序遍历，同邓公讲义
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
	void travLevel()//实现层次遍历，同邓公讲义
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
	scanf("%i%i",&n,&m);//输入n,m
	BinTree tree(n);//创建二叉树
	if(m==0)//按题目要求执行不同的函数
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