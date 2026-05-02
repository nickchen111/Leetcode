DIFFS = (0, 0, 1, -1, -1, 1, 1, -1, 0, 1)
class Solution:
    def rotatedDigits(self, n: int) -> int:
        '''
        不能有3,4,7, 至少要有2,5,6,9其中一個
        '''
        s = str(n)
        @cache
        def dfs(i:int, has_diff:bool, is_limit:bool) -> int:
            if i == len(s):
                return has_diff
            up = int(s[i]) if is_limit else 9
            ans = 0
            for d in range(0, up + 1):
                if DIFFS[d] != -1:
                    ans += dfs(i +1, has_diff or DIFFS[d], is_limit and d == up)
            return ans
        return dfs(0, False, True)