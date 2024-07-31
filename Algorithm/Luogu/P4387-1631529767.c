#include <stdio.h>
#include <stdlib.h>

int main()
{
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int max;
        scanf("%d", &max);
        int *in = (int*)malloc(sizeof(int) * (max + 1));
        int *out = (int*)malloc(sizeof(int) * (max + 1));
        int *Stack = (int*)malloc(sizeof(int) * (max + 1));
        int stackTop = -1;
        int flag = 1;
        for (int i = 0; i < max; i++)
        {
            scanf("%d", &in[i]);
        }
        for (int i = 0; i < max; i++)
        {
            scanf("%d", &out[i]);
        }
        int inIndex = 0, outIndex = 0;
        while (1)
        {
            if (in[inIndex] == out[outIndex]){
                inIndex++;
                outIndex++;
            }else if (stackTop > -1 && Stack[stackTop] == out[outIndex]){
                outIndex++;
                stackTop--;
            }else{
                if (inIndex > max - 1){
                    break;
                }
                Stack[++stackTop] = in[inIndex++];
                if (stackTop > max - 1){
                    flag = 0;
                    break;
                }
            }
        }
        if (flag == 0 || stackTop > -1){
            printf("No\n");
        }else{
            printf("Yes\n");
        }
        free(in);
        free(out);
        free(Stack);
    }
    return 0;
}