//
// Created by cx on 2021-10-12.
//
#include <cstdio>
#include <cstdlib>
#define MAXSIZE 100
typedef struct {
    int* base;
    int* top;
    int size;
}Stack;
void CreateStack(Stack* s)
{
    s->base = (int*)malloc(sizeof(int)*10);
    if(!s->base)
    {
        printf("Distribute false");
        exit(0);
    }
    s->top=s->base;
    s->size=MAXSIZE;
}
void Push(Stack* s,int n)
{
    int m;
    while(n/10!=0)
    {
        m=n%10;
        n/=10;
        *s->top++ = m;
    }
    m=n%10;
    *s->top++ = m;
}
int Pop(Stack* s) {
    if (s->base == s->top)
    {
        //栈空无法退栈
        exit(0);
    }
    int n=*(--s->top);
    return n;
}
void print(int n)
{
    if(n/10!=0)
        print(n/10);
    if(n/10==0)
        printf("%d",n%10);
    else
        printf(" %d",n%10);
}
void Stack_print(int n)
{
    int m;
    int flag=0,time=0;
    Stack s;
    CreateStack(&s);
    Push(&s,n);
    while(s.base!=s.top)
    {
        m= Pop(&s);
        if(time==0)
            printf("%d",m);
        else
            printf(" %d",m);
        time++;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    Stack_print(n);
    printf("\n");
    print(n);
    return 0;
}
