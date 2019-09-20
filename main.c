#include <stdio.h>

int add(int a, int b)
{
    return a+b;
}

int max(int a, int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    printf("Hello World"); 
    
    int a = 2;
    int b = 3;
    int x = max(a,b);
}
