#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
typedef int Elemtype;
typedef struct OLNode {
    int i, j; //非零元素的行，列
    Elemtype e; //元素的值
    OLNode* right, * down; //指向行下一节点和列下一节点的指针
}OLNode, * OLink;
typedef struct {
    OLink* rhead, * chead;
    int mu, nu, tu;//行数，列数，非零元素个数
}CrossList;
void Swap(int* a, int* b)
{
    //交换两个int型变量
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void Swap_Ptr(OLink a)
{
    //交换OLink结点的right和down关系
    OLNode* temp;
    temp = a->right; //存的是a的行关系，换的是行关系
    a->right = a->down;
    a->down = temp;
}
void Swap_Head(CrossList* mat)
{
    //交换十字链表总的行列关系
    OLink* temp; //存储行头节点的临时变量
    temp=(OLink*) malloc(sizeof(OLink)*mat->nu); //开辟同矩阵列数一样的空间
    for(int i=0;i<mat->nu;i++)
    {
        temp[i]=mat->chead[i];  //将矩阵的每列头结点依次放入temp中
    }
    mat->chead=(OLink*) realloc(mat->chead, sizeof(OLink)*mat->mu);
    //重新给矩阵的列开辟和矩阵行相同大小的空间
    for(int i=0;i<mat->mu;i++)
    {
        mat->chead[i]=mat->rhead[i]; //将每行的头结点赋给每列的列结点，实现列转行
    }
    mat->rhead=(OLink*) realloc(mat->rhead, sizeof(OLink)*mat->nu);
    //重新给矩阵的行开辟和矩阵列相同大小的空间
    for(int i=0;i<mat->nu;i++)
    {
        mat->rhead[i]=temp[i]; //将temp中存储的列头结点的地址依次赋给新的列头结点
    }//实现了行列头结点的互换
}
void CreateMatrix(CrossList* mat)
{
    //初始化稀疏矩阵
    int m, n, t; //定义矩阵的规模
    ifstream myfile("E:\\Clion\\read.txt");//打开文件，读取矩阵规模
    if(!myfile.is_open())
    {
        printf("Read.txt open failed.");
        return;
    }
    myfile>>m>>n>>t;
    mat->mu = m; mat->nu = n; mat->tu = t;
    mat->rhead = (OLink*)malloc(m * sizeof(OLink));//行头指针开辟m行头结点
    mat->chead = (OLink*)malloc(sizeof(OLink) * n);//列头指针开辟n列头结点
    if (!mat->rhead || !mat->chead)
    {
        exit(0);//开辟不成功程序结束
    }
    for (int i = 0; i < m; i++)
    {
        mat->rhead[i] = NULL;//将每行头结点设置为NULL
    }
    for (int i = 0; i < n; i++)
    {
        mat->chead[i] = NULL;//将每列头结点设置为NULL
    }
    int i, j, e, k; //存储节点的行列位置及元素值
    for (k = 0; k < t; k++)
    {
        myfile>>i>>j>>e;//从文件中读取行列，值赋给i，j，e
        OLink p = (OLNode*)malloc(sizeof(OLNode));
        if (!p)
            exit(0);
        p->i = i;
        p->j = j;
        p->e = e;
        if (mat->rhead[i] == NULL || mat->rhead[i]->j > j)
        {
            //如果行头结点为空，或者行头结点的列值大于当前结点的列值
            //则结点应插入在行头结点前
            p->right = mat->rhead[i];
            mat->rhead[i] = p;//行头指针始终指向第一个结点
        }
        else
        { //找在行中插入的位置
            OLink q = mat->rhead[i]; //遍历找插入位置
            while (q->right && q->right->j < j)
            {
                q = q->right;
            }
            p->right = q->right;
            q->right = p; //插入结点
        }
        if (mat->chead[j] == NULL || mat->chead[j]->i > i)
        {
            //原理同上
            p->down = mat->chead[j];
            mat->chead[j] = p;
        }
        else
        {
            OLink q = mat->chead[j];
            while (q->down && q->down->i < i)
            {
                q = q->down;
            }
            p->down = q->down;
            q->down = p;
        }
    }
}
void Reposition(CrossList* mat) {
    int i;
    OLNode* temp;//存储node节点行上下一位置结点的指针
    OLink node;
    for (i = 0; i < mat->mu; i++) {
        node = mat->rhead[i]; //每次令node指向行头结点
        while (node) {
            temp = node->right; //每次令node在行上向右移动
            Swap(&(node->i), &(node->j)); //交换结点的行列位置
            Swap_Ptr(node); //交换节点的right，down指针，即行列指向的关系
            node = temp; //行结点指针右边移
        }
    }
    Swap_Head(mat); //交换矩阵的总头结点，互换rhead和chead
    Swap(&mat->mu, &mat->nu); //交换矩阵的行数和列数
}
void Print(CrossList* mat)
{
    for (int i = 0; i < mat->mu; ++i) {
        OLNode* pcur = mat->rhead[i]; //遍历每行，打印矩阵
        int j = 0; //设置循环变量i，j
        while (pcur) {
            while (j != pcur->j) {
                //当j未达到p的j时，说明第j位前全为0
                cout << "0 ";
                ++j;
            }
            //输出0后输出元素
            cout << pcur->e << " ";
            //p后移
            pcur = pcur->right;
            ++j;
        }
        while (j != mat->nu) {
            //当该行未结束时，补0
            cout << "0 ";
            ++j;
        }
        cout << endl;
    }
    cout<<endl;
}
void Readin(CrossList* mat)
{
    fstream outfile;
    outfile.open("E:\\Clion\\exp.txt",ios::out);
    //打开文件
    if(!outfile)
    {
        printf("open failed");
    }
    for(int i=0;i<mat->mu;i++)
    {
        OLink p=mat->rhead[i];
        //按照每行将数据写入文件
        int j=0;
        while(p)
        {
            while(j!=p->j)
            {
                //原理同Print函数
                outfile<<"0 ";
                j++;
            }
            outfile<<p->e<<" ";
            p=p->right;
            j++;
        }
        while(j!=mat->nu)
        {
            outfile<<"0 ";
            j++;
        }
        outfile<<"\n";
    }
    //结束关闭文件
    outfile.close();
}
int main() {
    CrossList mat;
    CreateMatrix(&mat);
    printf("输入的稀疏矩阵为:\n");
    Print(&mat);
    printf("转置后的稀疏矩阵为:\n");
    Reposition(&mat);
    Print(&mat);
    Readin(&mat);
    return 0;
}
