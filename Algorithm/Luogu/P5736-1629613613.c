#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Dir {
    int n;
    struct Dir *next;
} Data;

Data *getnumber(int n);  //获取n个整数；
Data *del_errow_number(Data *head); //从链表中删除不符合的数字
bool isP(int n);  //判断是不是质数
void printfmain(Data *head);  //输出链表中的元素

int main()
{
    int n;
    scanf("%d", &n);
    Data *alpha = getnumber(n);
    alpha = del_errow_number(alpha);
    printfmain(alpha);
    return 0;
}

Data *getnumber(int n)  //获取n个整数；
{
    Data *p, *head, *last;
    head = last = NULL;
    for (int i=0; i<n; i++)
    {
        int number;
        scanf("%d",&number);
        p = (Data*)malloc(sizeof(Data));
        p->n = number;
        p->next = NULL;
        if (last != NULL){
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = p;
        }else {
            head = last = p;
        }
    }
    return head;
}

Data *del_errow_number(Data *head) //从链表中删除不符合的数字
{
    Data *p, *q, *r;
    q = r = NULL;
    r = head;
    while (head)
    {
        p = head;
        if (!isP(head->n)){
            if (q!=NULL){
                q->next = p->next;
                head = q;
                free(p);
                p = head;
            }else {
                head = head->next;
                r = head;
                free(p);
                continue;
            }
        }
        head = head->next;
        q = p;
    }
    return r;
}

bool isP(int n)  //判断是不是质数
{
    if (n<2){
        return 0;
    }else if (n==2){
        return 1;
    }else {
        for (int i=2; i<n; i++)
        {
            if (n%i==0){
                return 0;
            }
        }
        return 1;
    }
}

void printfmain(Data *head)  //输出链表中的元素
{
    int set=0;
    for (head; head; head = head->next)
    {
        if (set){
            printf(" ");
        }
        printf("%d",head->n);
        set=1;
    }
}