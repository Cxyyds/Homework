//
// Created by cx on 2021-10-31.
//
#include <cstdio>
#include <cstdlib>
#include <iostream>
#define MAXSIZE 20
using namespace std;
typedef struct TreeNode* BinTree;
typedef char ElementType;
struct TreeNode{
    ElementType data;
    BinTree left;
    BinTree right;
};
    typedef struct {
    BinTree* base;
    int front;
    int rear;
}Queue;

void InitQueue(Queue* Q)
{
    Q->base=(BinTree*) malloc(sizeof(TreeNode*)*MAXSIZE);
    if(!Q->base)
    {
        printf("内存分配失败");
        exit(0);
    }
    Q->front=Q->rear=0;
}
void InsertQueue(Queue* Q,BinTree BT)
{
    if((Q->rear+1)%MAXSIZE==Q->front)
    {
        printf("队列已满，无法插入");
        exit(0);
    }
    Q->base[Q->rear]=BT;
    Q->rear=(Q->rear+1)%MAXSIZE;
}

BinTree DeleteQueue(Queue* Q)
{
    if(Q->rear==Q->front)
    {
        printf("队列为空");
        exit(0);
    }
    int k=Q->front;
    Q->front=(Q->front+1)%MAXSIZE;
    return Q->base[k];
}
BinTree CreatTree()
{
    ElementType ch;
    BinTree BT;
    cin>>ch;
    if(ch=='#')
    {
        BT=NULL;
    }
    else {
        BT=(BinTree) malloc(sizeof(TreeNode));
        BT->data=ch;
        BT->left=CreatTree(); //递归创建左子树
        BT->right=CreatTree(); //递归创建右子树
    }
    return BT;
}
//先序遍历二叉树
void PreOrderTraversal(BinTree BT)
{
    if(BT)
    {
        printf("%3c",BT->data);
        PreOrderTraversal(BT->left);
        PreOrderTraversal(BT->right);
    }
}
//中序遍历二叉树
void InOrderTraversal(BinTree BT)
{
    if(BT)
    {
        InOrderTraversal(BT->left);
        printf("%3c",BT->data);
        InOrderTraversal(BT->right);
    }
}
//后序遍历二叉树
void PostOrderTraveral(BinTree BT)
{
    if(BT)
    {
        InOrderTraversal(BT->left);
        InOrderTraversal(BT->right);
        printf("%3c",BT->data);
    }
}
//层次遍历二叉树
void LevelOrderTraversal(BinTree BT)
{
    Queue Q;
    BinTree Temp;
    if(!BT)
    {
        return;
    }
    InitQueue(&Q);
    InsertQueue(&Q,BT);
    while(Q.front!=Q.rear)
    {
        Temp= DeleteQueue(&Q);
        printf("%3c",Temp->data);
        if(Temp->left)
        {
            InsertQueue(&Q,Temp->left);
        }
        if(Temp->right)
        {
            InsertQueue(&Q,Temp->right);
        }
    }
}
int main()
{
    BinTree BT=CreatTree();
    PreOrderTraversal(BT);
    printf("\n");
    InOrderTraversal(BT);
    printf("\n");
    LevelOrderTraversal(BT);
    return 0;
}

