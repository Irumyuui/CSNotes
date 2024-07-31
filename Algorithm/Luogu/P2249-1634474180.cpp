#include <iostream>

using namespace std;

int *arr, len;

int Find(int x, int begin, int end)
{
    int mid;
    while (begin < end)
    {
        mid = begin + ((end - begin) >> 1);
        if (arr[mid] >= x){
            end = mid;
        }else{
            begin = mid + 1;
        }
    }
    if (arr[begin] == x){
        return begin;
    }else{
        return -1;
    }
}

int main()
{
    int n;
    cin >> len >> n;
    arr = new int[len + 1];
    for (int i = 1; i <= len; ++i)
    {
        cin >> arr[i];
    }
    int space = 0;
    while (n--)
    {
        int x;
        cin >> x;
        if (space == 1){
            cout << " ";
        }else{
            space = 1;
        }
        cout << Find(x, 1, len);
    }
    return 0;
}