class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        n = len(nums)
        u = 1 << n
        mx = ans = 0
        sub_xor = [0] * u
        for i, x in enumerate(nums):
            mask = 1 << i
            for j in range(mask):
                new_mask = j | mask
                sub_xor[new_mask] = sub_xor[j] | x
                if sub_xor[new_mask] > mx:
                    ans = 1
                    mx = sub_xor[new_mask]
                elif sub_xor[new_mask] == mx:
                    ans += 1
        return ans