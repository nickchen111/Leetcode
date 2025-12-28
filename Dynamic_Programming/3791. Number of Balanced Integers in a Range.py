# TC:O(n^2 * D^2) n = log(high) D 為10 SC:O(n^2 * D)
class Solution:
    def countBalanced(self, low: str, high: str) -> int:
        def solve(num: str) -> int:
            n = len(num)
            @cache
            def dfs(pos: int, diff: int, is_limit: bool, is_started: bool) -> int:
                if pos == n:
                    return 1 if (is_started and diff == 0) else 0
                
                res = 0
                limit = int(num[pos]) if is_limit else 9
                if not is_started:
                    res = res + dfs(pos + 1, 0, False, False)
                for digit in range(0 if is_started else 1,limit + 1):
                    new_diff = diff + (digit if pos % 2 == 0 else -digit)
                    res = res + dfs(pos + 1, new_diff, is_limit and digit == limit, True)
                
                return res
            
            return dfs(0, 0, True, False)
        return solve(str(high)) - solve(str(int(low) - 1))
