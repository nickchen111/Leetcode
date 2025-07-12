# logtrick: TC:O(n*log(U)) SC:O(1) Sliding Window + Stack : TC:O(n) SC:O(1)
class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = inf
        for i, x in enumerate(nums):
            if abs(x - k) < ans: ans = abs(x - k)
            for j in range(i-1, -1, -1):
                if nums[j] | x == nums[j]: break
                nums[j] |= x
                if abs(nums[j] - k) < ans: ans = abs(nums[j] - k)
        return ans
class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = inf
        left = right_or = bottom = 0
        for right, x in enumerate(nums):
            right_or |= x
            while left <= right and (nums[left] | right_or) > k:
                # cal
                ans = min(ans, (nums[left] | right_or) - k)
                left += 1
                if bottom <= left:
                    # 重新計算stack 
                    for i in range(right - 1, left - 1, -1):
                        nums[i] |= nums[i + 1]
                    bottom = right
                    right_or = 0
            if left <= right:
                ans = min(ans, abs((nums[left] | right_or) - k))
        return ans
