#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef struct TreeNode* BinTree;   //指向二叉树结点的指针
typedef int ElementType;
struct TreeNode{
    ElementType data;  //存储二叉树结点的数据，类型为char
    BinTree left;   //指向结点左儿子的指针
    BinTree right; //指向结点右儿子的指针
};
//先序遍历创建二叉树，返回树的根节点
BinTree CreateTree()
{
    BinTree BT; //创建结点
    int n;  //数据域的值
    cin>>n;
    if(n==0)    //输入为0表示为空结点
    {
        BT=NULL;
    }
    else{
        BT=(BinTree) malloc(sizeof(TreeNode)); //为结点开辟空间
        BT->data=n;
        BT->left=CreateTree();  //递归创建左子树
        BT->right=CreateTree(); //递归创建右子树
    }
    return BT;  //返回根节点
}
void PreOrderTraversal(BinTree BT)
{
    //先序遍历二叉树
    if(BT){
        printf("%3d",BT->data);
        PreOrderTraversal(BT->left);
        PreOrderTraversal(BT->right);
    }
}
void getSum(BinTree BT,int& sum) //传入引用，使遍历时值在一个变量上更改
{
    //获取二叉树中所有数据域值并求和
    if(BT)
    {
        //先序遍历每经过一个结点便访问
        sum+=BT->data;  //sum加数据域的值
        if(BT->left)    //递归访问左子树求和
            getSum(BT->left,sum);
        if(BT->right)  //递归访问右子树求和
            getSum(BT->right,sum);
    }
}
void FindMax(BinTree BT,int& max)
{
    //遍历二叉树求各数据域中的最大值
    if(BT)
    {   //如果遍历到的当前结点数据域值大于max(传入时为0)
        if(BT->data>=max)
        {
            //则更改max的值
            max=BT->data;
        }
        if(BT->left)    //递归遍历左子树求最大值
            FindMax(BT->left,max);
        if(BT->right)   //递归遍历右子树求最大值
            FindMax(BT->right,max);
    }
}
void CountLow0(BinTree BT,int& count)
{
    //计数二叉树中小于0的数据的个数
    if(BT)
    {
        if(BT->data<0)
        {
            //如果遍历到的结点的数据域的值小于0，计数器+1
            count++;
        }
        if(BT->left)    //递归遍历左子树访问结点
            CountLow0(BT->left,count);
        if(BT->right)   //递归遍历右子树访问结点
            CountLow0(BT->right,count);
    }
}
int main() {
    int MaxNum=0;   //用于保存二叉树中最大值的结点数据
    int Low0Num=0;  //计数器，计数二叉树中值小于0的结点数
    int Sum=0;      //保存二叉树所有结点数据域的和
    BinTree BT=CreateTree();    //创建二叉树
    PreOrderTraversal(BT);  //先序遍历二叉树
    getSum(BT,Sum); //获取二叉树数据域的和
    FindMax(BT,MaxNum); //寻找二叉树结点值的最大值
    CountLow0(BT,Low0Num);  //计数二叉树中值小于0的节点数
    printf("\nSum is %d",Sum);
    printf("\nMaxNum is %d",MaxNum);
    printf("\nCount of the numbers which are lower than 0: %d",Low0Num);
    return 0;
}
