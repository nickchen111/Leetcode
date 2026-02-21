prime = {2, 3, 5, 7, 11, 13, 17, 19}
class Solution:
    def countPrimeSetBits(self, left: int, right: int) -> int:

        def solve(x: int) -> int:
            bits = list(map(int, bin(x)[2:]))
            n = len(bits)

            @cache
            def dfs(i: int, cnt1: int, is_limit: bool) -> int:
                if i == n:
                    return 1 if cnt1 in prime else 0

                upper = bits[i] if is_limit else 1
                ans = 0
                for d in range(upper + 1):
                    ans += dfs(i + 1, cnt1 + d, is_limit and d == upper)
                return ans

            return dfs(0, 0, True)

        return solve(right) - solve(left - 1)