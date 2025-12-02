class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        '''
        x -> y 
        然後就是乘法原理
        '''
        MOD = 10 ** 9 + 7
        mp = defaultdict(int)
        for x, y in points:
            mp[y] += 1
        tot = ans = 0
        for x in mp.values():
            tot += x * (x - 1) // 2
        for x in mp.values():
            cur = x * (x - 1) // 2
            ans += cur * (tot - cur)
        return ans // 2 % MOD
        