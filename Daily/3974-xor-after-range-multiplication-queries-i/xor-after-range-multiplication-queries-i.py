class Solution:
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:
        MOD = 10 ** 9 + 7
        for l, r, k, v in queries:
            for i in range(l, r + 1, k):
                nums[i] *= v
                nums[i] %= MOD
        return reduce(xor, nums)