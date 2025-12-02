class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        '''
        x -> y 
        然後就是乘法原理
        '''
        MOD = 10 ** 9 + 7
        mp = defaultdict(list)
        for x, y in points:
            mp[y].append(x)
        if len(mp) == 1:
            return 0
        tot = ans = 0
        for arr in mp.values():
            x = len(arr)
            tot += x * (x - 1) // 2
        for arr in mp.values():
            x = len(arr)
            cur = x * (x - 1) // 2
            ans += cur * (tot - cur)
        return ans // 2 % MOD
        