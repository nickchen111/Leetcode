# TC:O(128 ^ k) 大致上 但實際上大概2e5因為每層不可能都有128個 SC:O(k)
MX = 100001
divisors = [[] for _ in range(MX)]
for i in range(1, MX):
    for j in range(i, MX, i):
        divisors[j].append(i)
class Solution:
    def minDifference(self, n: int, k: int) -> List[int]:
        '''
        用k個數字相乘可以是n，並且這些數字任兩個diff要進量小 -> 二分
        首先要猜最大跟最小 這可以去對他做因數分解 -> 2^16 ~= 1e5
        16個去搭配選or不選
        '''
        minDiff = inf
        path = [0] * k
        ans = None
        def dfs(i:int, n:int, mn:int, mx:int) -> None:
            nonlocal minDiff
            nonlocal ans
            if i == k - 1:
                d = max(n, mx) - min(n, mn)
                if d < minDiff:
                    minDiff = d
                    path[i] = n
                    ans = path.copy()
                return
            for d in divisors[n]:
                path[i] = d
                dfs(i + 1, n // d, min(d, mn), max(d, mx))
            
        dfs(0, n, inf, -inf)
        return ans
