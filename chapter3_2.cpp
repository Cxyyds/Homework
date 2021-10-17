#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct {
    int* base;
    int* top;
    int size;
}NumStack;
typedef struct {
    char* base;
    char* top;
    int size;
}OpStack;
void InitNumStack(NumStack* s)
{
    s->base= (int*)malloc(sizeof(int)*MAXSIZE);
    if(!s->base)
    {
        printf("Distribute false");
        return;
    }
    s->top=s->base;
    s->size=MAXSIZE;
}
void InitOpStack(OpStack* s)
{
    s->base=(char*) malloc(sizeof(char)*MAXSIZE);
    if(!s->base)
    {
        printf("Distribute false");
        return;
    }
    s->top=s->base;
    s->size=MAXSIZE;
}
void PushNum(NumStack* s,int e)
{
    if(s->top-s->base>=s->size)
    {
        s->base=(int*) realloc(s->base,sizeof((s->size+MAXSIZE)* sizeof(int)));
        if(!s->base)
        {
            exit(0);
        }
        s->top=s->top+MAXSIZE;
        s->size+=MAXSIZE;
    }
    *s->top=e;
    s->top++;
}
void PopNum(NumStack* s,int* e)
{
    if(s->base==s->top)
    {
        printf("Distribute false");
        exit(0);
    }
    *e=*(--s->top);
    return;
}
void PushOp(OpStack* s,char e)
{
    if(s->top-s->base>=s->size)
    {
        s->base=(char*) realloc(s->base,sizeof((s->size+MAXSIZE)* sizeof(char)));
        if(!s->base)
        {
            exit(0);
        }
        s->top=s->top+MAXSIZE;
        s->size+=MAXSIZE;
    }
    *s->top=e;
    s->top++;
}
void PopOp(OpStack* s,char* e)
{
    if(s->base==s->top)
    {
        printf("Distribute false");
        exit(0);
    }
    *e=*(--s->top);
    return;
}
char getTop(OpStack* s)
{
    return *(s->top-1);
}
int grade(char c)
{
        if (c == '(')
            return 1;
        else if (c == '#')
            return 0;
        else if (c == '+' || c == '-')
            return 2;
        else if (c == '*' || c == '/')
            return 3;
        else
            return 4; //如果是右括号，则需连续退栈
}
int compare(char ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='#')
        return 1;
    else if(ch=='('||ch==')')
        return 2;
    else
        exit(0);
}
int compute(int num1,char ch,int num2)
{
    int result;
    switch (ch) {
        case '+':
            result=num1+num2;
            break;
        case '-':
            result=num1-num2;
            break;
        case '*':
            result=num1*num2;
            break;
        case '/':
            result=num1/num2;
            break;
    }
    return result;
}
void ToSuffix(char str[])
{
    OpStack s;
    int flag=0;
    char ch,temp;
    InitOpStack(&s);
    int i=0;
    while(str[i]!='\0')
    {
        flag=0;
        if(str[i]>='0'&&str[i]<='9')
        {
            printf("%c",str[i]);
        }
        else if(compare(str[i])==1)
        {
            if(s.top==s.base) {
                flag=1;
                PushOp(&s, str[i]);
            }
            else{
                while(s.base!=s.top)
                {
                    ch= getTop(&s);
                    if(grade(ch)>=grade(str[i]))
                    {
                        PopOp(&s,&temp);
                        printf("%c",ch);
                    }
                    else
                        break;
                }
            }
            if(str[i]!='#'&&flag==0)
            {
                PushOp(&s,str[i]);
            }
        }
        else if(compare(str[i])==2)
        {
            if(str[i]=='(')
            {
                PushOp(&s,str[i]);
            }
            else
            {
                while(getTop(&s)!='(')
                {
                    PopOp(&s,&temp);
                    printf("%c",temp);
                }
                PopOp(&s,&temp);
            }
        }
        i++;
    }

    printf("\n");
}

int Expression()
{
    NumStack OPND;
    OpStack OPTR;
    int i=0,j=0;
    char temp;
    InitNumStack(&OPND);
    InitOpStack(&OPTR);
    char str[50];
    gets(str);
    ToSuffix(str);
    char ch;//获取运算符
    int num1,num2;//获取操作数栈弹出的数字
    int result=0;
    while(str[i]!='\0')
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            PushNum(&OPND,(str[i]-'0'));
        }
        else if(compare(str[i])==1)
        {
            if(OPTR.base==OPTR.top)
            {
                PushOp(&OPTR,str[i]);
            }
            else{
                while(OPTR.base!=OPTR.top)
                {
                    ch= getTop(&OPTR);
                    if(grade(ch)>=grade(str[i]))
                    {
                        PopNum(&OPND,&num1);
                        PopNum(&OPND,&num2);
                        result= compute(num2,ch,num1);
                        PopOp(&OPTR,&temp);
                        PushNum(&OPND,result);
                    }
                    else
                        break;
                }
                if(str[i]!='#')
                {
                    PushOp(&OPTR,str[i]);
                }
            }
        }
        else if(compare(str[i])==2)
        {
            if(str[i]=='(')
            {
                PushOp(&OPTR,str[i]);
            }
            else{
                //如果是右括号，一直退栈
                while(getTop(&OPTR)!='(')
                {
                    ch= getTop(&OPTR);
                    PopNum(&OPND,&num1);
                    PopNum(&OPND,&num2);
                    result= compute(num2,ch,num1);
                    PopOp(&OPTR,&temp);
                    PushNum(&OPND,result);
                }
                PopOp(&OPTR,&temp);//左括号只退栈不输出
            }
        }
        i++;
    }
    while(OPTR.base!=OPTR.top)
    {
        ch= getTop(&OPTR);
        PopNum(&OPND,&num1);
        PopNum(&OPND,&num2);
        result= compute(num2,ch,num1);
        PopOp(&OPTR,&temp);
        PushNum(&OPND,result);
    }
    return result;
}
int main()
{
    int num=Expression();
    printf("%d",num);
    return 0;
}
