#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
typedef struct TreeNode* BinTree;   //指向二叉树结点的指针
typedef char ElementType;
struct TreeNode {
    ElementType data;  //存储二叉树结点的数据，类型为char
    BinTree left;   //指向结点左儿子的指针
    BinTree right; //指向结点右儿子的指针
};
BinTree CreatTree()
{
    //先序递归法创建二叉树
    ElementType ch;
    BinTree BT; //创建一个指向树根结点的指针
    cin >> ch; //输入结点数据域内容
    if (ch == '#')
    {
        //输入#停止函数在创建树过程中某一方向的递归
        BT = NULL;  //设置指针为空
    }
    else {
        BT = (BinTree)malloc(sizeof(TreeNode));//为指针开辟空间存储数据
        BT->data = ch;
        BT->left = CreatTree(); //递归创建左子树
        BT->right = CreatTree(); //递归创建右子树
    }
    return BT; //递归结束返回根节点
}
//先序遍历二叉树
void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        //第一次经过结点就进行访问
        printf("%3c", BT->data);
        PreOrderTraversal(BT->left); //递归遍历左子树
        PreOrderTraversal(BT->right); //递归遍历右子树
    }
}
void getElem(BinTree BT, int num, ElementType& e,int& time)
{
    if (BT)
    {
        time++;
        if (time == num) {
            e = BT->data;
            return;
        }
        if (BT->left)
            getElem(BT->left, num, e, time);
        if (BT->right)
        {
            getElem(BT->right, num, e, time);
        }

    }
}

void CountLeaves(BinTree BT,int& count)
{
    if(BT)
    {
        if(!BT->left&&!BT->right)
        {
            count++;
        }
        if(BT->left)
            CountLeaves(BT->left,count);
        if(BT->data)
            CountLeaves(BT->right,count);
    }
}
int TreeHeight(BinTree BT)
{
    if(!BT)
        return 0;
    int hl,hr;
    hl= TreeHeight(BT->left);
    hr= TreeHeight(BT->right);
    return (hl>=hr)?hl+1:hr+1;
}
void changeTree(BinTree BT)
{
    if(BT)
    {
        if(BT->left&&BT->right||BT->left&&!BT->right||!BT->left&&BT->right)
        {
            BinTree Temp=BT->left;
            BT->left=BT->right;
            BT->right=Temp;
        }
        if(BT->left)
            changeTree(BT->left);
        if(BT->right)
            changeTree(BT->right);
    }
}
void FindDepth(BinTree BT,ElementType x,int& height){
    if(BT)
    {
        if(BT->data==x)
        {
            height=TreeHeight(BT);
            return;
        }
        if(BT->left)
            FindDepth(BT->left,x,height);
        if(BT->right)
            FindDepth(BT->right,x,height);
    }
}
void CreateTree1(BinTree* BT,char s[])
{
    int length= strlen(s);
    int i,j;
    BinTree Temp;
    BinTree Nodes[20];
    for(i=0,j=0;i< length;i++)
    {
        if(s[i]=='#')
        {
            Temp=NULL;
        }
        else
        {
            Temp=(BinTree) malloc(sizeof(TreeNode));
            Temp->data=s[i];
            Temp->left=Temp->right=NULL;
        }
        if(i==0)
        {
            *BT=Temp;
        }
        else{
            while(i/2!=j)
                j++;
            if(2*j==i)
            {
                Nodes[i]->left=Temp;
            }
            if(2*j+1==i){
                Nodes[i]->right=Temp;
            }
        }
        Nodes[i]=Temp;
    }
}
int main() {
    char e;
    int time = 0;
    int count=0;
    int height=0;
    BinTree BT = CreatTree();
    getElem(BT, 3, e,time);
    PreOrderTraversal(BT);
    CountLeaves(BT,count);
    FindDepth(BT,'A',height);
    printf("\n%c leaf:%d  height:%d", e,count,height);
    return 0;
}
