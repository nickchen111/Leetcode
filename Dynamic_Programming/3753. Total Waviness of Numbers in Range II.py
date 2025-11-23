# TC:O(100 * logn) SC:O(100 * logn)
class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        def check(num: int) -> int:
            if num < 100:
                return 0
            s = str(num)
            n = len(s)
            @cache
            def dfs(i: int, waviness:int, is_limit: bool, is_num: bool, last_cmp: int, last_num: int) -> int:
                if i == n:
                    return waviness
                limit = int(s[i]) if is_limit else 9
                ans = 0
                if not is_num:
                    ans = dfs(i + 1, 0, False, False, last_cmp, last_num)
                start = 0 if is_num else 1
                for d in range(start, limit + 1):
                    w = waviness
                    c = (d > last_num) - (d < last_num) if is_num else 0 # 1 代表valley, -1:peak, 0 nothing
                    if c * last_cmp < 0:
                        w += 1
                    ans += dfs(i + 1, w, is_limit and d == limit, is_num or d > 0, c, d)
                return ans
            return dfs(0, 0, True, False, 0, -1)
        return check(num2) - check(num1 - 1)
