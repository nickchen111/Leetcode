# TC:O(n) SC:O(n)
class Solution:
    def minDistinctFreqPair(self, nums: list[int]) -> list[int]:
        cnt = Counter(nums)
        x = min(nums)
        cnt_min = cnt[x]

        min_y = min((y for y, c in cnt.items() if c != cnt_min), default=None)
        if min_y is None:
            return [-1, -1]
        return [x, min_y]
