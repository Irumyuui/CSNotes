
ans = 0
def dfs(id : int, less : int, bef : int, arr : list):
    global ans
    if less == 0:
        tmp = 0
        for i in range(id, len(arr)):
            tmp = tmp * 10 + arr[i]
        ans = max(ans, max(tmp, 1) * bef)
        return
    elif id >= len(arr):
        return
    tmp = 0
    for i in range(id, len(arr) - less + 1):
        tmp = tmp * 10 + arr[i]
        dfs(i + 1, less - 1, bef * max(tmp, 1), arr)
    
n, k = map(int, input().split())
arr = [int(i) for i in input()]
arr = [1] + arr
dfs(1, k + 1, 1, arr)
print(ans)