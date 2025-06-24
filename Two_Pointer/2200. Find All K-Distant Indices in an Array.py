# TC:O(n) SC:O(1)
class Solution:
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        n = len(nums)
        r = 0
        ans= []
        for j in range(n):
            if nums[j] == key:
                l = max(r, j - k)
                r = min(n-1, j +ｋ) + 1
                for i in range(l, r):
                    ans.append(i)
        return ans
