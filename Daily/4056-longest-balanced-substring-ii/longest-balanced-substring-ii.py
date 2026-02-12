class Solution:
    def longestBalanced(self, s: str) -> int:
        # 第一種情況
        n = len(s)
        i = ans = 0
        while i < n:
            j = i + 1
            while j < n and s[i] == s[j]:
                j += 1
            ans = max(ans, j - i)
            i = j
        # 不同有兩個的情況
        def f(x:str, y:str) -> None:
            nonlocal ans
            i = 0
            while i < n:
                pos = {0: i - 1}
                d = 0
                while i < n and (s[i] == x or s[i] == y):
                    d += 1 if s[i] == x else -1
                    if d in pos:
                        ans = max(ans, i - pos[d])
                    else:
                        pos[d] = i
                    i += 1
                i += 1
        f('a', 'b')
        f('a', 'c')
        f('b', 'c')
        # a b c
        pos = {(0, 0): -1}
        cnt = defaultdict(int)
        for i, b in enumerate(s):
            cnt[b] += 1
            p = (cnt['a'] - cnt['b'], cnt['b'] - cnt['c'])
            if p in pos:
                ans = max(ans, i - pos[p])
            else:
                pos[p] = i
        return ans
        
                
                    

