class Solution:
    def repeatedNTimes(self, nums: List[int]) -> int:
        mp = defaultdict(int)
        target = len(nums) // 2
        for x in nums:
            mp[x] += 1
            if mp[x] == target:
                return x
        return -1
