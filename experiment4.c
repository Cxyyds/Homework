#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
void getNext(char* s, int* next)
{
	//先获取子串t1的next数组
    int j = 0;
    int k = -1;
    next[0] = -1;
    while (s[j] != '\0')
    {
        if (k == -1 || s[j] == s[k])
        {
            ++k;
            next[++j] = k;
        }
        else
            k = next[k];//回退到k位字符的位置
    }
}
void getNextval(char* s, int nextval[])
{
	//根据子串的next获取改进的nextval
    int j, k;
    nextval[0] = k = -1;
    j = 1;
    while (s[j])
    {
        if (k == -1 || s[j - 1] == s[k])
            if (s[++k] == s[j])
                nextval[j++] = nextval[k];
            else
                nextval[j++] = k;
        else
            k = nextval[k];
    }
}
int Length(char* s)
{
	//获取串的长度
    return strlen(s);
}
int ReplaceSolution(char* s, char* t1, int nextval[], int pos1[])
{
    int i = 0, j = 0;
int count = 0;
//由KMP算法寻找子串的位置并存储在pos1中，
    while (s[i] && t1[j]) {
        if (j == -1 || s[i] == t1[j]) {
            i++;
            j++;//相同字符则一起后移
        }
        else
            j = nextval[j];//回退子串的位置
        if (!t1[j])
        {
            pos1[count] = i - j;//将子串在主串中的位置存储在pos1中
            pos2[count] = i; //将子串末位的下一位位置存在pos2中，便于拼接时锁定位置
            count++; //子串出现次数+1
            j = 0;
        }
    }
    return count;
}
void Combination(char* s, char* t1, char* t2, int pos1[],int count, char* newstr)
{
	//将主串s中的子串t1换为t2,方法为将两串拼接到一新串中
    int index = 0, position = 0;
    int i, j, k;
    for (i = 0; i < count; i++)
{
	//循环count次，将t1全部换为t2
        for (j = position; j < pos1[i]; j++)
        {
			//在新串中将原t1子串前的s主串内容放入新串
            newstr[index++] = s[j];
        }
        for (k = 0; k < Length(t2); k++)
        {
			//将需替换的t2子串的内容插入到原t1的位置
            newstr[index++] = t2[k];
        }
		//将下次主串插入新串的位置锁定在t1串的下一个字符
        position = pos1[i] + Length(t1);
    }
        while (position < Length(s))
        {
			//全部替换完后若主串剩下部分未插入新串，则将其填入
            newstr[index++] = s[position++];
        }
        newstr[index] = '\0';  //结束新串
}
int main() {
    char s[50]; //存储主串
    char newstr[50]; //存储替换后的新串
    char t1[50]; //子串
    char t2[50]; //需替换的子串
    int nextval[50]; //存储子串的nextval值
    int count = 0; //记录主串中子串出现的次数
    int pos1[50]; //记录子串在主串中的位置
    printf("请输入主串内容：");
    cin >> s;
    printf("请输入查找的子串内容：");
    cin >> t1;
    printf("请输入要替换的子串内容：");
    cin >> t2;
    getNext(t1, nextval); //先获取子串的next
    getNextval(t1, nextval); //根据子串的next获取nextval
    count = ReplaceSolution(s, t1, nextval, pos1); //获取子串在主串中出现的次数
    Combination(s, t1, t2, pos1, count, newstr); //实现子串的替换，存在新串中
    printf("子串出现的次数为：%d   ", count);
    printf("替换后的子串为：%s", newstr);
    return 0;
}
