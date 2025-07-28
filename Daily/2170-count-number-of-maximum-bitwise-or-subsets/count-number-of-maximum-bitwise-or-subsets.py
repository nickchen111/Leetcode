class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        n = len(nums)
        u = 1 << n
        mx = 0
        sub_xor = [0] * u
        for i, x in enumerate(nums):
            mask = 1 << i
            for j in range(mask):
                sub_xor[j | mask] = sub_xor[j] | x
                mx = max(mx, sub_xor[j | mask])
        ans = 0
        for i in range(u):
            if sub_xor[i] == mx:
                ans += 1
        return ans