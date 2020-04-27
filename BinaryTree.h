#ifndef BTREE
#define BTREE

#include <stdio.h>
#include "Stack.h"
#include "Queue.h"

typedef char ElemType;

typedef struct BTree
{
	ElemType data;
	struct Node* lchild;
	struct Node* rchild;
}BiTNode, *BiTree;

typedef enum Status {
	SUCCESS = 1,
	ERROR = 0,
}Status;


BiTree CreateBiTree(void);
Status visit(BiTree T);
Status PreOrderTraverse(BiTree T);//先序递归
Status InOrderTraverse(BiTree T);//中序递归
Status PostOrderTraverse(BiTree T);//后序递归
Status show_level(BiTree T);//层序遍历
Status destory(BiTree T);
int Value(BiTree T);
#endif
