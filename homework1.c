//
// Created by cx on 2021-10-12.
//
#include <cstdio>
#include <cstdlib>
void print(int n)
{
    if(n/10!=0)
        print(n/10);
    if(n/10==0)
        printf("%d",n%10);
    else
        printf(" %d",n%10);
}
int main(){
    int m;
    scanf("%d",&m);
    print(m);
    return 0;
}
