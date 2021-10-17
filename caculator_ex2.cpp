#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef char SqType;
typedef int NumType;
struct OpStack {
    SqType* base;
    SqType* top;
    int size;
};//存储运算符的栈
struct NumStack {
    NumType* base;
    NumType* top;
    int size;
};//存储操作数的栈
//初始化栈的函数
void InitOpStack(OpStack* stack)
{
    stack->base = (SqType*)malloc(sizeof(SqType) * STACK_INIT_SIZE);
    if (!stack->base)
    {
        printf("Distribute failed");
        exit(0);
    }
    stack->top = stack->base;
    stack->size = STACK_INIT_SIZE;
    return;
}
void InitNumStack(NumStack* stack)
{
    stack->base = (NumType*)malloc(sizeof(NumType) * STACK_INIT_SIZE);
    if (!stack->base)
    {
        printf("Distribute failed");
        exit(0);
    }
    stack->top = stack->base;
    stack->size = STACK_INIT_SIZE;
    return;
}
//将元素压入栈中
int PushOp(OpStack* stack, SqType elem)
{
    //插入元素elem为新的栈顶元素
    //首先判断栈是否已经满了
    if (stack->top - stack->base >= STACK_INIT_SIZE)
    {
        //重新分配内存给新栈
        stack->base = (SqType*)realloc(stack->base, (stack->size + STACK_INCREMENT) * sizeof(SqType));
        if (!stack->base)
        {
            printf("Distribute failed");
            return 0;
        }
        //先到进栈的位置，再增加栈的大小
        stack->top = stack->base + stack->size;
        stack->size += STACK_INCREMENT;
    }
    *(stack->top++) = elem;
    return 1;
}
int PushNum(NumStack* stack, NumType elem)
{
    //插入元素elem为新的栈顶元素
    //首先判断栈是否已经满了
    if (stack->top - stack->base >= STACK_INIT_SIZE)
    {
        //重新分配内存给新栈
        stack->base = (NumType*)realloc(stack->base, (stack->size + STACK_INCREMENT) * sizeof(NumType));
        if (!stack->base)
        {
            printf("Distribute failed");
            return 0;
        }
        //先到进栈的位置，再增加栈的大小
        stack->top = stack->base + stack->size;
        stack->size += STACK_INCREMENT;
    }
    *(stack->top++) = elem;
    return 1;
}
//将栈顶元素弹出并存于elem中
bool PopOp(OpStack* stack, SqType* elem)
{
    //如果不是空栈就删除stack的栈顶元素，并返回删除的元素
    if (stack->top == stack->base)
    {
        printf("The Opstack is empty.");
        exit(0);
        return false;
    }
    *elem = *(--stack->top);
    return true;
}
//将栈顶元素弹出并存于elem中
bool PopNum(NumStack* stack, NumType* elem)
{
    //如果不是空栈就删除stack的栈顶元素，并返回删除的元素
    if (stack->top == stack->base)
    {
        printf("The Numstack is empty.");
        exit(0);
        return false;
    }
    *elem = *(--stack->top);
    return true;
}
//获取运算符栈的栈顶元素
SqType getTop(OpStack* stack)
{
    if (!stack->base)
    {
        printf("The stack is empty.");
        exit(0);
    }
    return *(stack->top - 1);
}
//判断输入的字符是否是运算符
int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '#')
        return 1;
    else if (ch == '(' || ch == ')')
        return 2;
    else
    {
        printf("The operator is not allowed!");
        exit(0);
    }
}
//将运算符进行量化处理，按照运算符优先级分类
int compare(char c)
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
//对栈中弹出的元素进行计算，返回计算结果
int compute(int a, char c, int b)
{
    int num;
    switch (c) {
        case '+':
            num = a + b;
            break;
        case '-':
            num = a - b;
            break;
        case '*':
            num = a * b;
            break;
        case '/':
            num = a / b;
            break;
    }
    return num;
}
//计算表达式结果，并将表达式的计算结果返回
int Expression(OpStack* OPTR, NumStack* OPND)
{
    //形参分别为运算符栈和操作数栈
    InitNumStack(OPND);
    InitOpStack(OPTR);
    //栈底插入开始运算符#
    int i = 0, j = 0;//两个循环变量
    int flag1 = 0;//判断首个数字是否为负数的标志变量
    int flag2 = 0;//判断括号内的首个数字是否为负数的标志变量
    int num = 0;
    int a = 0;//储存多位数，并压入栈
    int temp1, temp2;//存储弹出的操作数
    char ch;//操作符栈顶元素
    char c;//接受退栈的运算符
    char s[100];//输入的表达式
    scanf("%s", s);//获取表达式，由于需要判定多位数，需要一次输入表达式
    while (s[i] != '\0')
    {
        //每次循环重置标志变量与多位数的值
        flag1 = 0;
        flag2 = 0;
        a = 0;
        j = i;//分别处理运算符和数字
        if (s[j] >= '0' && s[j] <= '9') //如果是数字，看是否是多位数
        {
            if (j == 1 && s[0] == '-')
            {
                //如果是第一个数字并且数字前有符号，判定为负数
                flag1 = 1;
            }
            if (s[j - 1] == '-' && s[j - 2] == '(')
            {
                //如果括号后的第一个数带负号则判定为负数
                flag2 = 1;
            }
            while (s[j] >= '0' && s[j] <= '9')
            {
                //计算多位数
                a = (s[j] - '0') + a * 10;
                j++;
            }
            //计算运算符的位置
            i = --j;
            if (flag1 == 1 || flag2 == 1)
            {
                //如果有一个成立，则压入负数值
                PushNum(OPND, -a);
            }
            else {
                PushNum(OPND, a);
            }
        }
        else if (isOperator(s[i]) == 1)
        {
            //如果是+，-，*，/运算，进行判断计算
            if (OPTR->base == OPTR->top)
            {
                //如果是空栈，考虑是不是负号，负号不入栈
                if (i == 0 && s[i] == '-')
                {
                    //如果是负数则负号进栈再出栈
                    PushOp(OPTR, s[i]);
                    PopOp(OPTR, &c);
                }
                else
                    //否则直接进栈
                    PushOp(OPTR, s[i]);
            }
            else {
                //如果栈非空，则考虑进栈运算符和栈顶运算符的优先级
                while (OPTR->base != OPTR->top) {
                    ch = getTop(OPTR);//取出栈顶的操作符
                    if (compare(ch) >= compare(s[i])) {
                        //如果栈顶运算符优先级比入栈运算符优先级高则出栈运算
                        PopNum(OPND, &temp1);
                        PopNum(OPND, &temp2);
                        num = compute(temp2, ch, temp1);
                        PopOp(OPTR, &c);
                        PushNum(OPND, num);
                    }
                    else
                        break;
                }
                if (s[i] != '#')
                {
                    if (s[i - 1] == '(' && s[i] == '-')
                    {
                        //如果(后是负号，说明是一个负数，将负号弹出栈
                        PushOp(OPTR, s[i]);
                        PopOp(OPTR, &c);
                    }
                    else {
                        PushOp(OPTR, s[i]);
                    }
                }
            }
        }
            //如果是括号运算符，进行计算
        else if (isOperator(s[i]) == 2)
        {
            if (s[i] == '(')
            {
                //左括号无条件进栈
                PushOp(OPTR, s[i]);
            }
            else
            {
                //右括号则对两括号中的内容进行出栈运算
                while (getTop(OPTR) != '(')
                {
                    ch = getTop(OPTR);
                    PopNum(OPND, &temp1);
                    PopNum(OPND, &temp2);
                    num = compute(temp2, ch, temp1);
                    //取两数和一个运算符进行计算，结果压入操作数栈中
                    PopOp(OPTR, &c);
                    PushNum(OPND, num);
                }
                PopOp(OPTR, &c);
            }
        }
        i++;//计数器增加
    }
    while (OPTR->base != OPTR->top)
    {
        //如果运算符栈未空，则继续计算
        ch = getTop(OPTR);
        //取栈顶运算符和两个操作数计算
        PopNum(OPND, &temp1);
        PopNum(OPND, &temp2);
        num = compute(temp2, ch, temp1);
        PopOp(OPTR, &c);
        PushNum(OPND, num);
        //得到最终结果num
    }
    //返回计算结果
    return num;
}
int main() {
    NumStack OPND;
    OpStack OPTR;
    printf("Please input expression:");
    printf("\nresult is: %d\n", Expression(&OPTR, &OPND));
}
