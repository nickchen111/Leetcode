# TC:O(n) SC:O(1)
class Solution:
    def maximumValueSum(self, nums: List[int], k: int, edges: List[List[int]]) -> int:
        '''
        XOR 兩次等於沒變, 所以這題完全可以說是問說XOR偶數次可以得到的最大值是多少
        f[i][j] : 走到i為止 XOR odd or even 的最大元素和是多少
        f[i][0] = max(f[i-1][0] + x, f[i-1][1] + (x ^k))
        f[i][1] = max(f[i-1][1] + x, f[i-1][0] + (x ^k))
        '''
        # 空間優化
        f0, f1 = 0, -inf
        for x in nums:
            f0, f1 = max(f0 + x, f1 + (x ^ k)), max(f1 + x, f0 + (x ^ k))
        return f0

        '''
        遞推
        n = len(nums)
        f = [[-inf] * 2 for _ in range(n+1)]
        f[0][0] = 0
        for i in range(n):
            x = nums[i]
            f[i+1][0] = max(f[i][0] + x, f[i][1] + (x ^ k))
            f[i+1][1] = max(f[i][1] + x, f[i][0] + (x ^ k))
        return f[n][0]
        '''
