class Solution:
    def soupServings(self, n: int) -> float:
        if n >= 4451:
            return 1
        @cache
        def dfs(a:int, b:int) -> float:
            if a <= 0 and b <= 0:
                return  0.5
            if a <= 0 and b > 0:
                return 1
            if a > 0 and b <= 0:
                return 0
            return (dfs(a - 100, b - 0) + dfs(a - 75, b - 25) + dfs(a - 50, b - 50) + dfs(a - 25, b - 75)) / 4
        return dfs(n, n)