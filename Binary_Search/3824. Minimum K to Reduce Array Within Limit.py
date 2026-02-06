# TC:O(nlogU) SC:O(1)
class Solution:
    def minimumK(self, nums: List[int]) -> int:
        left = 1
        right = 2 * 10 ** 5
        def check(mid:int) -> bool:
            ans = 0
            for x in nums:
                if x > 0:
                    ans += (x + mid - 1) // mid
            return ans <= mid * mid
        while left < right:
            mid = left + (right - left) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return left
