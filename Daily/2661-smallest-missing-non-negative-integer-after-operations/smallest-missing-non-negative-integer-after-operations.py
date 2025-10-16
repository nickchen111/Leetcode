class Solution:
    def findSmallestInteger(self, nums: List[int], m: int) -> int:
        cnt = [0] * m
        for x in nums:
            cnt[x % m] += 1

        i = cnt.index(min(cnt))
        return m * cnt[i] + i
