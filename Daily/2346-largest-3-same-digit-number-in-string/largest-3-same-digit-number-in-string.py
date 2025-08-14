class Solution:
    def largestGoodInteger(self, num: str) -> str:
        n = len(num)
        ans = ""
        for i in range(1, n - 1):
            if num[i] == num[i-1] and num[i] == num[i + 1]:
                ans = max(ans, num[i])
                i += 1
        return ans * 3