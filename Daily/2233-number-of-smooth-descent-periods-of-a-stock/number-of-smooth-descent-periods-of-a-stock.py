class Solution:
    def getDescentPeriods(self, prices: List[int]) -> int:
        ans = 0
        i = 0
        n = len(prices)
        while i < n:
            j = i + 1
            while j < n and prices[j] + 1 == prices[j - 1]:
                j += 1
            ans += (j - i + 1) * (j - i) // 2
            i = j
        return ans