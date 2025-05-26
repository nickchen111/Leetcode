# TC:O(n ^ 3) SC:O(n ^ 2)
def is_consecutive(x: str, y: str) -> bool:
    d = abs(ord(x) - ord(y))
    return d == 1 or d == 25
class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:
        n = len(s)
        can_empty = [[False] * n for _ in range(n)]
        for i in range(n):
            if i + 1 < n and is_consecutive(s[i], s[i + 1]):
                can_empty[i][i + 1] = True
        for i in range(n - 2, -1, -1):
            can_empty[i + 1][i] = True  # 空串
            for j in range(i + 1, n, 2):
                if is_consecutive(s[i], s[j]) and can_empty[i + 1][j - 1]:
                    can_empty[i][j] = True
                    continue
                for k in range(i + 1, j - 1, 2):
                    if can_empty[i][k] and can_empty[k +1][j]:
                        can_empty[i][j] = True
                        break
        f = [''] * (n + 1)
        for i in range(n-1, -1, -1):
            ans = s[i] + f[i + 1]
            for j in range(i + 1, n, 2):
                if can_empty[i][j]:
                    ans = min(ans, f[j + 1])
            f[i] = ans
        return f[0]
            
        '''
        遞歸
        @cache
        def can_empty(i:int, j:int) -> bool:
            if i > j:
                return True
            if is_consecutive(s[i], s[j]) and can_empty(i + 1, j - 1):
                return True
            for k in range(i + 1, j - 1, 2):
                if can_empty(i, k) and can_empty(k + 1, j):
                    return True
            return False
        @cache
        def dfs(i:int) -> str:
            if i == n:
                return ""
            ans = s[i] + dfs(i + 1)
            for j in range(i + 1, n, 2):
                if can_empty(i, j):
                    ans = min(ans, dfs(j + 1))
            return ans
        return dfs(0)
        '''
            
        
        
