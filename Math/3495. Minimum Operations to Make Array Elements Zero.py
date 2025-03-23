# TC:O(nlgU) lg以四為底 U為區間最大範圍 SC:O(1)
class Solution:
    def minOperations(self, queries: List[List[int]]) -> int:
        def f(n:int) -> int:
            m = n.bit_length()
            res = sum((i+1) // 2  << (i-1) for i in range(1, m))
            return res + (m + 1) // 2 * (n + 1 - (1 << m >> 1))
        ans = 0
        for l, r in  queries:
            ans += (f(r) - f(l-1) + 1) // 2 # 上取整 + 1
        return ans
