
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include "BinaryTree.h"

//这个创建树的函数需要交互输入， 有点麻烦，但是可以建立所有二叉树
//一开始输入根节点， 接着输入左子树、右子树，依次类推，# 表示对应子树为空
BiTree CreateBiTree(void)
{
	BiTree pnode;
	char temp;

	temp = getchar();
	getchar();  //skip /n
	if (temp == '#')
		return NULL;

	pnode = (BiTree)malloc(sizeof(BiTNode));
	if (pnode == NULL)
	{
		return NULL;
	}
	pnode->data = temp;
	printf("Enter left child data (# to NULL): ");
	pnode->lchild = CreateBiTree();
	printf("Enter right child data(# to NULL): ");
	pnode->rchild = CreateBiTree();

	return pnode;
}

Status visit(BiTree T) {

	printf("该节点数据为：%c \n", T->data);
	return SUCCESS;
}

Status PreOrderTraverse(BiTree T)//递归
{
	if (T == NULL)
		return ERROR;
	visit(T);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);

	return SUCCESS;
}

Status InOrderTraverse(BiTree T)//递归
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		visit(T);
		InOrderTraverse(T->rchild);
	}
	return SUCCESS;
}

Status PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		visit(T);
	}
	return SUCCESS;
}

Status LevelOrderTraverse(BiTree T)//层序遍历
{
	Queue q;
	Elem e;

	if (!T)
		return ERROR;
	initQueue(&q);

	e.elem = T;
	enqueue(&q, &e);
	while (!isEmpty(&q))
	{
		dequeue(&q, &e);
		T = (BiTree)e.elem;
		visit(T);
		if (T->lchild)
		{
			e.elem = T->lchild;
			enqueue(&q, &e);
		}
		if (T->rchild)
		{
			e.elem = T->rchild;
			enqueue(&q, &e);
		}
	}

	return SUCCESS;
}

Status destory(BiTree T)
{
	if (T == NULL)
		return ERROR;
	if (T->lchild != NULL)
		destory(T->lchild);//销毁左子树
	if (T->rchild != NULL)
		destory(T->rchild);//销毁右子树
	free(T);//释放当前结点

	printf("已销毁");
	return SUCCESS;
}

int Value(BiTree T) {
	if (T == NULL)
		return 0;
	if (T->data <= '9' && T->data >= '0')
		return (T->data - '0');
	else
	{
		switch (T->data)            //因为这一步的T->data必为运算符，则必有左右孩子节点且不空
		{
		case'+':  return Value(T->lchild) + Value(T->rchild); break;
		case'-':  return Value(T->lchild) - Value(T->rchild); break;
		case'*':  return Value(T->lchild) * Value(T->rchild); break;
		case'/':  return Value(T->lchild) / Value(T->rchild); break;
		}
	}

}

int main(void)
{
	BiTree tree;
	printf("请输入根节点数据：\n");

	tree = CreateBiTree();
	printf("先序遍历:\n ");
	PreOrderTraverse(tree);
	
	printf("\n中序遍历:\n ");
	InOrderTraverse(tree);

	printf("\n后序遍历:\n ");
	PostOrderTraverse(tree);
	
	printf("\n层序遍历:\n ");
	LevelOrderTraverse(tree);
	printf("\n");

	destory(tree);
	return 0;
}
