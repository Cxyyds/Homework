#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef int Elemtype;
typedef struct OLNode {
    int i, j;
    Elemtype e;
    OLNode* right, * down;
}OLNode, * OLink;
typedef struct {
    OLink* rhead, * chead;
    int mu, nu, tu;//行数，列数，非零元素个数
}CrossList;
void Swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void Swap_Ptr(OLink a)
{
    OLNode* temp;
    temp = a->right; //存的是a的行关系，换的是行关系
    a->right = a->down;
    a->down = temp;
}
void Swap_Head(CrossList* mat)
{
    OLink* temp;
    temp=(OLink*) malloc(sizeof(OLink)*mat->nu);
    for(int i=0;i<mat->nu;i++)
    {
        temp[i]=mat->chead[i];
    }
    mat->chead=(OLink*) realloc(mat->chead, sizeof(OLink)*mat->mu);
    for(int i=0;i<mat->mu;i++)
    {
        mat->chead[i]=mat->rhead[i];
    }
    mat->rhead=(OLink*) realloc(mat->rhead, sizeof(OLink)*mat->nu);
    for(int i=0;i<mat->nu;i++)
    {
        mat->rhead[i]=temp[i];
    }
}
void CreateMatrix(CrossList* mat)
{
    int m, n, t; //定义矩阵的规模
    printf("输入矩阵的规模：");
    cin >> m >> n >> t;
    mat->mu = m; mat->nu = n; mat->tu = t;
    mat->rhead = (OLink*)malloc(m * sizeof(OLink));
    mat->chead = (OLink*)malloc(sizeof(OLink) * n);
    if (!mat->rhead || !mat->chead)
    {
        exit(0);
    }
    for (int i = 0; i < m; i++)
    {
        mat->rhead[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        mat->chead[i] = NULL;
    }
    int i, j, e, k;
    for (k = 0; k < t; k++)
    {
        printf("输入节点的行号，列号，值:");
        cin >> i >> j >> e;
        OLink p = (OLNode*)malloc(sizeof(OLNode));
        if (!p)
            exit(0);
        p->i = i;
        p->j = j;
        p->e = e;
        if (mat->rhead[i] == NULL || mat->rhead[i]->j > j)
        {
            p->right = mat->rhead[i];
            mat->rhead[i] = p;//更换第一个元素为p
        }
        else
        { //找在行中插入的位置
            OLink q = mat->rhead[i];
            while (q->right && q->right->j < j)
            {
                q = q->right;
            }
            p->right = q->right;
            q->right = p;
        }
        if (mat->chead[j] == NULL || mat->chead[j]->i > i)
        {
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
    OLNode* temp;//将结点的right，down关系互换
    OLink node;
    for (i = 0; i < mat->mu; i++) {
        node = mat->rhead[i];
        while (node) {
            temp = node->right;
            Swap(&(node->i), &(node->j));
            Swap_Ptr(node);
            node = temp; //行结点指针右边移
        }
    }
    Swap_Head(mat);
    Swap(&mat->mu, &mat->nu);
}
void OLMatPrint(CrossList* mat)
{
    for (int i = 0; i < mat->mu; ++i) {
        OLNode* pcur = mat->rhead[i];
        int nextj = 0;
        while (pcur) {
            while (nextj != pcur->j) {
                cout << "0 ";
                ++nextj;
            }
            cout << pcur->e << " ";
            pcur = pcur->right;
            ++nextj;
        }
        while (nextj != mat->nu) {
            cout << "0 ";
            ++nextj;
        }
        cout << endl;
    }
    cout<<endl;
}

int main() {
    CrossList mat;
    CreateMatrix(&mat);
    OLMatPrint(&mat);
    Reposition(&mat);
    OLMatPrint(&mat);
    return 0;
}
