class Solution:
    def triangleNumber(self, nums: List[int]) -> int:
        # 三角形 -> a + b > c sliding window
        n = len(nums)
        if n <= 2:
            return 0
        ans = 0
        nums.sort()
        for j in range(n - 1, 1, -1):
            l, r = 0, j - 1
            while l < r:
                if nums[l] + nums[r] > nums[j]:
                    ans += r - l
                    r -= 1
                else:
                    l += 1
        return ans

