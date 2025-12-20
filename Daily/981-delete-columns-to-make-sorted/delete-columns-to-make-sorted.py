class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        ans = 0
        m, n = len(strs), len(strs[0])
        for i in range(n):
            prev = 'a'
            for j in range(m):
                if strs[j][i] < prev:
                    ans += 1
                    break
                prev = strs[j][i]
        return ans
