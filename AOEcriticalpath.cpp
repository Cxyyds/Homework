#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#define MAXSIZE 30
#define MAXNUM 20
#define MAXSIZE 100
using namespace std;
int ve[MAXSIZE];    //储存各个节点的最早开始时间
int vl[MAXSIZE];    //存储各个结点的最晚开始时间
int e[MAXSIZE] = { 0 }; //存储关键路径的结点
int l[MAXSIZE] = { 0 }; //存储关键路径的结点
typedef struct  ArcNode {
    int adjvex; //边连接的点
    int w;  //边权重
    ArcNode* nextarc;   //指向下一顶点的边指针
};
typedef struct VNode {
    int data;
    ArcNode* firstarc;  //顶点表示一个数据加边指针
}VNode, AdjList[MAXNUM];
typedef struct {
    AdjList vexs;   //邻接表
    int vexnum, arcnum; //顶点个数以及边数
    int kind;   //表明图类型
}ALGraph;
typedef struct {    //栈的数据结构
    int* base;  //存储数据的基地址
    int* top;   //栈顶指针
    int size;   //栈的尺寸
}Stack;
void InitStack(Stack* s)
{
    //栈的初始化
    s->base = (int*)malloc(sizeof(int) * MAXSIZE);
    if (!s->base) {
        //开辟空间失败则退出程序
        exit(0);
    }
    s->top = s->base;   //栈顶指向基地址
    s->size = MAXSIZE;
}
int Push(Stack* s, int a)
{
    //将数据压入栈
    if (s->top - s->base >= MAXSIZE)
    {
        //如果栈满则重新分配内存给新栈
        s->base = (int*)realloc(s->base, (s->size + MAXSIZE) * sizeof(int));
        if (!s->base)
        {
            //分配失败则退出程序
            printf("Distribute failed");
            return 0;
        }
        //先到进栈的位置，再增加栈的大小
        s->top = s->base + s->size;
        s->size += MAXSIZE;
    }
    *(s->top++) = a;    //将元素a放入栈顶，栈顶指针上移
    return 1;
}
bool Pop(Stack* s, int* a) {
    //如果不是空栈就删除stack的栈顶元素，并返回删除的元素
    if (s->top == s->base) {
        printf("The Opstack is empty.");
        exit(0);
    }
    *a = *(--s->top);   //将栈顶元素赋给a
    return true;
}
void CreateGraph(ALGraph& G)
{
    //创建有向图的函数，从文件读入数据
    int i, j;
    int w;//边的权重
    ifstream file("E:\\Clionprogram\\DataStructure\\design.txt");
    if (!file) {
        //如果打开文件失败则退出程序
        cout << "open false" << endl;
        return;
    }
    cout << "读入图的结点个数" << endl;
    file >> G.vexnum;   //将顶点数赋给G.vexnum
    cout << "读入图的边数" << endl;
    file >> G.arcnum;   //将顶点数赋给G.arcnum
    for (i = 0; i < G.vexnum; i++)
    {
        G.vexs[i].data = i + 1; //每个顶点的值为i+1，序号为0-G.vexnum
        G.vexs[i].firstarc = NULL;  //指向下一顶点的边指针为空
    }
    printf("文件读入两点间的边（结点号从0开始）以及权重\n");
    for (int k = 0; k < G.arcnum; k++)
    {
        ArcNode* pr, * p, * q = (ArcNode*)malloc(sizeof(ArcNode)); //q为待指向弧
        file >> i >> j >> w; //读取两点序号以及权值
        q->adjvex = j;   //建立第i行表结点
        q->nextarc = NULL;  //设置边指针为空
        q->w = w;   //将权重赋给边
        pr = NULL;  //跟随指针设为NULL
        p = G.vexs[i].firstarc; //如果不为空表明i结点已有指向的结点
        while (p && p->adjvex < j)  //尾插法建立链表
        {
            pr = p; //pr指针跟随
            p = p->nextarc; //p后移
        }
        if (pr == NULL)
        {
            //表头插入时
            q->nextarc = p; //将q插入在p之前
            G.vexs[i].firstarc = q; //q插在邻接表头后
        }
        else
        {
            pr->nextarc = q;    //q插入pr和p之间
            q->nextarc = p;
        }
    }
}
int CalVex(ALGraph& G)
{
    //拓扑排序计算各事件的最早最晚开始事件并存于ve，vl数组中
    int* indegree = new int[G.vexnum];  //辅助数组，存储所有顶点入度
    int i, j, k, count = 0; //计数器初始化为0
    ArcNode* p;
    Stack S, T; //设置工作栈
    for (i = 0; i < G.vexnum; i++) {
        indegree[i] = 0;    //初始化辅助数组所有结点入度为0
    }
    for (i = 0; i < G.vexnum; i++) {
        for (p = G.vexs[i].firstarc; p != NULL; p = p->nextarc) {
            indegree[p->adjvex]++;  //每遍历到一个顶点，该顶点入度+1
        }
    }
    //初始化辅助工作栈
    InitStack(&S);
    InitStack(&T);
    //以下开始前向递推(拓扑排序)
    for (i = 0; i < G.vexnum; i++) {
        ve[i] = 0;  //初始化最早开始时间均为0
    }
    for (i = 0; i < G.vexnum; i++) {
        if (!indegree[i]) {
            //遍历所有顶点，寻找源点，indegree=0表示入度为0，为源点
            Push(&S, i);//源点入栈S
            k = i;  //保存源点位置
            break;
        }
    }
    while (S.base != S.top) {
        Pop(&S, &i);    //栈顶元素出栈
        Push(&T, i);
        count++;    //计数是否所有顶点都入栈
        for (p = G.vexs[i].firstarc; p; p = p->nextarc) {
            if (!(--indegree[p->adjvex])) {
                Push(&S, p->adjvex);//减去一度后若入度为0则按拓扑排序入栈
            }
            double w = ve[i] + p->w;    //前一点的最早开始时间+边权做后继点的最早开始时间的选择之一
            if (ve[p->adjvex] < w) {
                ve[p->adjvex] = w;    //取两者的最大值做该点的最早开始时间
            }
        }
    }
    delete[]indegree;   //清除辅助数组空间
    if (count < G.vexnum) {
        return -1;  //如果count<顶点数说明有环，退出
    }
    if (T.base != T.top) {
        Pop(&T, &j);//汇点出栈  赋值于j
    }
    //所有顶点最晚开始时间初始化为汇点最早开始时间
    for (i = 0; i < G.vexnum; i++) {
        vl[i] = ve[j];
    }
    while (T.base != T.top) {
        Pop(&T, &i);  //前驱结点出栈，反推vl
        for (p = G.vexs[i].firstarc; p; p = p->nextarc) {
            int w = vl[p->adjvex] - p->w;   //当前结点最晚开始时间减去边权作为最晚开始时间的选择之一
            if (vl[i] > w) {    //如果前驱节点的最晚开始时间比w大，则赋i节点的最晚开始时间为w
                vl[i] = w;  //取min
            }
        }
    }
    return k;
}
void PrtKA(ALGraph& G)
{
    int count = 0;  //对e，l数组的大小计数
    printf("关键路径为：");
    int ee;
    int ll;
    int time = 0;//计算关键路径的最短工作时间
    ArcNode* p;
    for (int i = 0; i < G.vexnum; i++) {
        for (p = G.vexs[i].firstarc; p; p = p->nextarc) {
            //如果活动最早开始时间和最晚开始时间一致说明为关键活动
            ee = ve[i]; ll = vl[p->adjvex] - p->w;
            if (ee == ll) {
                //将一条路径的两点存入e，l中
                e[count] = i;
                l[count++] = p->adjvex;
                break;  //只记一条最短路径，找到一次退出
            }
        }
    }
    int i, j, k;
    //如果源点序号不是0号，此时关键路径顺序混乱，寻找源点
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            //遍历e,l数组中每一个元素，寻找第一个在l中没有找到的结点序号为源点
            if (e[i] == l[i]) {
                break;
            }
        }
        if (j == count)
            break;  //找到源点，退出循环
    }
    //遍历寻找与源点相连的下一关键活动并交换位置
    for (k = 0; i < count; i++) {
        if (e[k] == l[i]) {
            //找到相连的下一活动，交换e,l数组对应元素，保持源点为第一个点
            swap(e[i], e[k]);
            swap(l[i], l[k]);
        }
    }//找源点
    for (i = 1; i < count; i++) {
        //将e,l两个数组中出现的多余关键路径剔除
        for (j = 0; j < count; j++) {
            if (e[i] == l[j])
                break;
        }
        //如果遍历e后，l中没有与e[i]相同的元素，则该对应路径为多余路径，剔除
        if (j == count) {
            for (k = i; k < count; k++) {
                //将后续对应路径前移一位
                e[k] = e[k + 1];
                l[k] = l[k + 1];
            }
            //活动数-1
            count--;
            //i倒退一位
            i--;
        }
    }
    //输出关键路径上的活动
    for (i = 0; i < count; i++) {
        printf("<%d,%d>", e[i], l[i]);
    }
    cout << endl;
    //计算关键路径的最短完成时间
    for (i = 0; i < count; i++) {
        time += G.vexs[e[i]].firstarc->w;
    }
    printf("工作时间长度为：%d 个时间单位", time);
}
int main()
{
    ALGraph G;
    CreateGraph(G);
    CalVex(G);
    cout << "Ve[]序列为：";
    for (int i = 0; i < G.vexnum; i++) {
        printf("%3d", ve[i]);
    }
    cout << "\nVl[]序列为：";
    for (int i = 0; i < G.vexnum; i++) {
        printf("%3d", vl[i]);
    }
    cout << endl;
    PrtKA(G);
    return 0;
}
