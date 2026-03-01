class Solution:
    def minPartitions(self, n: str) -> int:
        # 找到最大的數字即可
        ans = 0
        for i in range(len(n)):
            ans = max(ans, int(n[i]))
        return ans