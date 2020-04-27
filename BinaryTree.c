
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include "BinaryTree.h"

//����������ĺ�����Ҫ�������룬 �е��鷳�����ǿ��Խ������ж�����
//һ��ʼ������ڵ㣬 �������������������������������ƣ�# ��ʾ��Ӧ����Ϊ��
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

	printf("�ýڵ�����Ϊ��%c \n", T->data);
	return SUCCESS;
}

Status PreOrderTraverse(BiTree T)//�ݹ�
{
	if (T == NULL)
		return ERROR;
	visit(T);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);

	return SUCCESS;
}

Status InOrderTraverse(BiTree T)//�ݹ�
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

Status LevelOrderTraverse(BiTree T)//�������
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
		destory(T->lchild);//����������
	if (T->rchild != NULL)
		destory(T->rchild);//����������
	free(T);//�ͷŵ�ǰ���

	printf("������");
	return SUCCESS;
}

int Value(BiTree T) {
	if (T == NULL)
		return 0;
	if (T->data <= '9' && T->data >= '0')
		return (T->data - '0');
	else
	{
		switch (T->data)            //��Ϊ��һ����T->data��Ϊ���������������Һ��ӽڵ��Ҳ���
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
	printf("��������ڵ����ݣ�\n");

	tree = CreateBiTree();
	printf("�������:\n ");
	PreOrderTraverse(tree);
	
	printf("\n�������:\n ");
	InOrderTraverse(tree);

	printf("\n�������:\n ");
	PostOrderTraverse(tree);
	
	printf("\n�������:\n ");
	LevelOrderTraverse(tree);
	printf("\n");

	destory(tree);
	return 0;
}
