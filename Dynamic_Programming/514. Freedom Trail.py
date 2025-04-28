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
# DP 二分預處理做法 較慢
class Solution:
    def findRotateSteps(self, ring: str, key: str) -> int:
        '''
        問說最少需要幾次才能拼湊出 key string 那就是順時針逆時針都檢查一次
        每一個位置到達他前後不同字都需要轉幾次
        要如何預處理每個位置可以走到哪些其他char, 其實不用預處理也可過
        需要這樣的資料結構 pos, 26個字母最近的兩個順時針跟逆時針是哪兩個
        可以有種結構是 某個字母出現的位置們 然後對他二分
        並且需要判斷這個字母是否是需要的
        '''
        n = len(ring)
        needed = set(key)
        ch_pos = {ch: [] for ch in needed}
        for i, ch in enumerate(ring):
            if ch in needed:
                ch_pos[ch].append(i)
        pos_ch = [
            {ch: [-1, -1] for ch in needed}
            for _ in range(n)
        ]
        # print(pos_ch)
        for i in range(n):
            for ch in needed:
                lst = ch_pos[ch]
                idx = bisect_left(lst, i)
                cw = lst[idx] if idx < len(lst) else lst[0]
                ccw = lst[idx-1] if idx > 0 else lst[-1]
                pos_ch[i][ch][0] = ccw
                pos_ch[i][ch][1] = cw

        @cache
        def dfs(key_i: int, ring_pos: int) -> int:
            if key_i == len(key):
                return 0
            target = key[key_i]
            best = inf
            for nbr in pos_ch[ring_pos][target]:
                diff = abs(nbr - ring_pos)
                step = min(diff, n - diff)
                cost = step + 1 + dfs(key_i + 1, nbr)
                if cost < best:
                    best = cost
            return best
        return dfs(0, 0)


        

