# TC:O(n^2 * gcd(U)) SC:O(1)
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        if all(x == 1 for x in nums):
            return 0
        one = 0
        for x in nums:
            if x == 1:
                one += 1
        if one:
            return n - one
        ans = inf
        # 找出gcd = 1 最短的array
        for i in range(n):
            g = nums[i]
            end = -1
            for j in range(i, n):
                g = gcd(g, nums[j])
                if g == 1:
                    end = j
                    break
            if g == 1:
                ans = min(ans, n - 1 + j - i)
        return ans if ans != inf else -1
