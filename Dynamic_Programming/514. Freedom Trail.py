# TC:O(n * m) SC:O(n * (m + 26))
class Solution:
    def findRotateSteps(self, s: str, t: str) -> int:
        s = [ord(c) - ord('a') for c in s]
        t = [ord(c) - ord('a') for c in t]
        n = len(s)
        m = len(t)
        pos = [0] * 26 
        for i, c in enumerate(s):
            pos[c] = i
        left = [None] * n
        for i, c in enumerate(s):
            left[i] = pos.copy() # pos[:]
            pos[c] = i
        for i in range(n-1, -1, -1):
            pos[s[i]] = i
        right = [None] * n
        for i in range(n-1, -1, -1):
            right[i] = pos.copy() # pos[:]
            pos[s[i]] = i
        '''
        遞推
        f = [[0] * n for _ in range(m + 1)]
        for i in range(m-1, -1, -1):
            c = t[i] 
            for j in range(n):
                if s[j] == c:
                    f[i][j] = f[i + 1][j]
                else:
                    l, r = left[j][c], right[j][c]
                    f[i][j] =  min( f[i+1][l] + min(n - abs(j - l), abs(j - l)), f[i+1][r] + min(n - abs(j - r), abs(j - r)))
        return f[0][0] + len(t)
        '''

        @cache 
        def dfs(i:int, pos:int):
            if i == len(t):
                return 0
            c = t[i]
            if s[pos] == c:
                return dfs(i + 1, pos)
            l, r = left[pos][c], right[pos][c]
            return min(dfs(i + 1, l) + min(n - abs(pos - l), abs(pos - l)), dfs(i + 1, r) + min(n - abs(pos - r), abs(pos - r)))
        return dfs(0, 0) + len(t)
# BFS TC:O(n * m) SC:O(n * m)
class Solution:
    def findRotateSteps(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        vis = [[False] * (m + 1) for _ in range(n)]
        vis[0][0] = True
        q = [(0, 0)]
        step = 0
        while True:
            tmp = q
            q = []
            for i, j in tmp:
                if j == m:
                    return step
                if s[i] == t[j]:
                    if not vis[i][j + 1]:
                        vis[i][j + 1] = True
                        q.append((i, j + 1))
                    continue
                for i2 in (i - 1) % n, (i + 1) % n:
                    if not vis[i2][j]:
                        vis[i2][j] = True
                        q.append((i2, j))
            step += 1

