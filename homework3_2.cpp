#include <cstdlib>
#include <cstdio>
#include <iostream>
#define MAXSIZE 100
using namespace std;
typedef char ElementType;
struct SqTree {
    ElementType* data;
    int length;
};
void InitSqTree(SqTree* BT)
{
    BT->data = (ElementType*)malloc(sizeof(ElementType) * MAXSIZE);
    if (!BT->data)
    {
        printf("分配空间失败");
        exit(0);
    }

    BT->length = 0;
}
void CreateTree(SqTree* BT, int index)
{
    ElementType ch;
    cin >> ch;
    if (ch == '#')
    {
        BT->data[index] = '\0';
        return;
    }
    else
    {
        BT->data[index] = ch;
        BT->length++;
        CreateTree(BT, 2 * index + 1);
        CreateTree(BT, 2 * index + 2);
    }
}
void PreOrderTraversal(SqTree* BT, int index)
{
    if (index < BT->length)
    {
        printf("%3c", BT->data[index]);
        PreOrderTraversal(BT, 2 * index + 1);
        PreOrderTraversal(BT, 2 * index + 2);
    }
}
void InOrderTraversal(SqTree* BT, int index)
{
    if (index < BT->length)
    {
        InOrderTraversal(BT, 2 * index + 1);
        printf("%3c", BT->data[index]);
        InOrderTraversal(BT, 2 * index + 2);
    }
}
void PostOrderTraversal(SqTree* BT, int index)
{
    if (index < BT->length)
    {
        PostOrderTraversal(BT, 2 * index + 1);
        PostOrderTraversal(BT, 2 * index + 2);
        printf("%3c", BT->data[index]);
    }
}
int main() {
    SqTree BT;
    InitSqTree(&BT);
    CreateTree(&BT, 0);
    printf("完全二叉树先序遍历为：");
    PreOrderTraversal(&BT, 0);
    printf("\n完全二叉树中序遍历为：");
    InOrderTraversal(&BT, 0);
    printf("\n完全二叉树后序遍历为：");
    PostOrderTraversal(&BT, 0);
    return 0;
}
