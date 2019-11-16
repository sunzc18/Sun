#include<stdio.h>
using namespace std;
struct BinNode
{
	BinNode* parent;
	BinNode* lc;
	BinNode* rc;
	int data;
	BinNode(){}
	BinNode(int num)
	{
		data = num;
		lc = NULL;
		rc = NULL;
		parent = NULL;
	}
	void insertAsLC(BinNode* p);
	void insertAsRC(BinNode* p);
};
void BinNode::insertAsLC(BinNode* p)
{
	lc=p;
	p->parent=this;
}
void BinNode::insertAsRC(BinNode* p)
{
	rc=p;
	p->parent=this;
}
class Stack 
{
	private:
		int _size;
		BinNode** stack;
		int top;
	public:
	Stack(int m)
	{
		_size = m;
		stack = new BinNode*[m];
		top = -1;
	}
	void push(BinNode* p)
	{
		stack[++top]=p;
	}
	BinNode* pop()
	{
		return stack[top--];
	}
	BinNode* Top()
	{
		return stack[top];
	}
	bool empty()
	{
		return top<0; 
	}
};
BinNode* RebuildTree(int n,int* pre,int* post)
{
	BinNode* temp=NULL;
	int Parent=0;
	int* _pre=new int[n];
	int* _post=new int[n];
	for(int i=0;i<n;i++)
	{
		_pre[pre[i]-1]=i;
		_post[post[i]-1]=i;
	}
	BinNode** bin=new BinNode*[n];
	for(int i=0;i<n;i++)
	{
		bin[i]=new BinNode(i+1);
	}
	Stack Build(n);
	Build.push(bin[0]);
	temp=Build.pop();
	bin[0]->insertAsLC(bin[pre[_pre[temp->data-1]+1]-1]);
	bin[0]->insertAsRC(bin[post[_post[temp->data-1]-1]-1]);
	Build.push(bin[post[_post[temp->data-1]-1]-1]);
	Build.push(bin[pre[_pre[temp->data-1]+1]-1]);
	while(!Build.empty())
	{
		temp=Build.pop();
		Parent=temp->parent->data;
		if((_pre[Parent-1]+2==_pre[post[_post[Parent-1]-1]-1])&&(temp->data==temp->parent->lc->data))continue;
		else if((_post[pre[_pre[Parent-1]+1]-1]+1==_post[Parent-1]-1)&&(temp->data==temp->parent->rc->data))continue;
		else
		{
			temp->insertAsLC(bin[pre[_pre[temp->data-1]+1]-1]);
			temp->insertAsRC(bin[post[_post[temp->data-1]-1]-1]);
			Build.push(bin[post[_post[temp->data-1]-1]-1]);
			Build.push(bin[pre[_pre[temp->data-1]+1]-1]);
		}
	}
	return bin[0];
}
void goAlongVine(BinNode* p,Stack& S)
{
	while(p!=NULL)
	{
		S.push(p);
//		printf("p->data=%d\n",p->data);
		p=p->lc;
	}
}
void trav(BinNode* p,int n)
{
	Stack S(n);
	while(true)
	{
		goAlongVine(p,S);
		if(S.empty())break;
		p=S.pop();
		printf("%d ",p->data);
		p=p->rc;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	int* pre=new int[n];
	int* post=new int[n];
	BinNode* p=NULL;
	for(int i=0;i<n;i++)
	{
		scanf("%d",&pre[i]);
	}
	for(int i=0;i<n;i++)
	{
		scanf("%d",&post[i]);
	}
	trav(RebuildTree(n,pre,post),n);
	return 0;
}
