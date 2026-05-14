class Solution:
    def isGood(self, nums: List[int]) -> bool:
        cnt = Counter(nums)
        mx = max(nums)
        n = len(nums)
        if mx != n - 1:
            return False
        num = 1
        while num < mx:
            if cnt[num] != 1:
                return False
            num += 1
        return True
