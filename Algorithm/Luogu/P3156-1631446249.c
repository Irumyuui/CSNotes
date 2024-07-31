#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int number[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &number[i]);
    }
    int s[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &s[i]);
    }
    for(int i = 0; i < m; i++)
    {
        printf("%d\n", number[s[i] - 1]);
    }
    return 0;
}