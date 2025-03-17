# TC:O(n^2 * k) SC:O(n*k)
class Solution:
    def checkPartitioning(self, s: str) -> bool:
        '''
        問說能否將string 切割三份 每一份都是回文串 
        劃分型 + 區間型判斷回文串DP
        '''
        n = len(s)
        is_p = [[False] * n for _ in range(n)]
        for i in range(n):
            is_p[i][i] = True
            if i + 1 < n and s[i] == s[i+1]:
                is_p[i][i+1] = True
        for i in range(n-3, -1, -1):
            for j in range(i+2, n):
                if s[i] == s[j] and is_p[i+1][j-1]:
                    is_p[i][j] = True
        f = [[False] * 4 for _ in range(n + 1)]
        f[0][0] = True
        for i in range(n):
            for j in range(i, -1, -1):
                if not is_p[j][i]: continue
                for k in range(3):
                    if f[j][k]:
                        f[i+1][k+1] = True
        return f[n][3]
        '''
        @cache
        def is_p(l:int, r:int) -> bool:
            if l >= r:
                return True
            if s[l] == s[r] and is_p(l+1, r-1):
                return True
            return False
        
        @cache
        def dfs(i:int, cnt:int) -> bool:
            if i < 0 and cnt == 3:
                return True
            if cnt > 3:
                return False
            for j in range(i, -1, -1):
                if is_p(j, i) and dfs(j-1, cnt + 1):
                    return True
            return False
        return dfs(n-1, 0)
        '''

        
