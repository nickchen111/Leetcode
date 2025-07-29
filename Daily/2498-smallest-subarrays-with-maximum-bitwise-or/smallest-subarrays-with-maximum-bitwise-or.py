class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [0] * n
        ans[-1] = 1
        if n == 1:
            return ans

        nums[-1] |= nums[-2]
        left_or, right, bottom = 0, n - 1, n - 2
        for left in range(n - 2, -1, -1):
            left_or |= nums[left]
            while right > left and (left_or | nums[right]) == (left_or | nums[right - 1]):
                right -= 1
                if bottom >= right:
                    for i in range(left + 1, right + 1):
                        nums[i] |= nums[i - 1]
                    bottom = left
                    left_or = 0
            ans[left] = right - left + 1
        return ans
