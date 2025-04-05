#include <stdio.h>
#include <math.h>

typedef struct Locate {
    double x;
    double y;
} L;

double dis(L a, L b);

int main(int argc, char *argv[])
{
    L a1, a2, a3;
    scanf("%lf%lf%lf%lf%lf%lf", &a1.x, &a1.y, &a2.x, &a2.y, &a3.x, &a3.y);
    double sumt = dis(a1, a2) + dis(a1, a3) + dis(a2, a3);
    printf("%.2f", sumt);
    return 0;
}

double dis(L a, L b)
{
    double result;
    result = sqrt(pow(fabs(a.x-b.x), 2)+pow(fabs(a.y-b.y), 2));
    return result;
}