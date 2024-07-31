#include <iostream>
#include <string>

using namespace std;

string zhongxu, houxu;
void ReBuildTree(int zl, int zr, int hl, int hr)
{
    cout << houxu[hr];
    for (int i = zl; i <= zr; ++i)
    {
        if (zhongxu[i] == houxu[hr]){
            if (i != zl){
                ReBuildTree(zl, i - 1, hl, hl + i - zl - 1);
            }
            if (i != zr){
                ReBuildTree(i + 1, zr, hl + i - zl, hr - 1);
            }
            break;
        }
    }
}

int main()
{
    cin >> zhongxu >> houxu;
    ReBuildTree(0, zhongxu.size() - 1, 0, houxu.size() - 1);
    return 0;
}