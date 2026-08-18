class Solution:
    def f(self, nums: List[int], x: int) -> int:
        return -1 if x in nums else x

    def largestInteger(self, nums: List[int], k: int) -> int:
        if k == len(nums):
            return max(nums)
        if k == 1:
            ans = -1
            for x, c in Counter(nums).items():
                if c == 1:
                    ans = max(ans, x)
            return ans
        # nums[0] 不能出现在其他地方，nums[-1] 同理
        return max(self.f(nums[1:], nums[0]), self.f(nums[:-1], nums[-1]))
