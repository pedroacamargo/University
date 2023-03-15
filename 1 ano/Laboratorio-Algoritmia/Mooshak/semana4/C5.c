#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 
int ver(char p[], int h)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = i + 1; j < h - 1; j++)
        {
            if (p[i] == p[j])
                return 0;
        }
    }
    return 1;
}

// ELEM -> 
int elem(char p[], int h)
{
    for (int i = 0; i < (int)strlen(p) - h + 1; i++)
    {
        if (ver(p + i, h)) return i;
    }
    return -1;
}


int main(){
    int n, h;
    char p[1000];

    if (scanf("%d", &n) != 1) return 1; 
    char t[n];

    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &h) != 1) return 1;

        if (scanf("%s", p) != 1) return 1;

        t[i] = elem(p, h);
    }
    for (int i = 0; i < n; i++)
        printf("%d\n", t[i]);
}
