class Solution:
    def flowerGame(self, n: int, m: int) -> int:
        if m == 0 and n == 0:
            return 0
        return (n // 2) * (m - ( m // 2)) + (m // 2) * (n - ( n // 2))