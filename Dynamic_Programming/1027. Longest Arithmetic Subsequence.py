# DP TC:O(n^2) SC:O(n^2) 枚舉公差 TC:O(m * (m + n)) m為nums最大值 SC:O(m)
class Solution:
    def longestArithSeqLength(self, nums: List[int]) -> int:
        '''
        求最長的等差數列 
        會讓人想到去沒舉可能的等差數列狀況
        數字大小從0-500 所以最大的等差只會是500 可能是-500 ~ 500
        '''
        # 枚舉公差
        ans = 0
        m = max(nums)
        for d in range(-m, m + 1):
            f = [0] * (m + 1)
            for x in nums:
                f[x] = f[x - d] + 1 if 0 <= x - d <= m else 1
            ans = max(ans, max(f))
        return ans

        '''
        遞推
        f = [{} for _ in range(len(nums))]
        for i, x in enumerate(nums):
            for j in range(i - 1, -1, -1):
                d = x - nums[j]  # 公差
                if d not in f[i]:
                    f[i][d] = f[j].get(d, 1) + 1
        return max(max(d.values()) for d in f[1:])
        '''

        '''
        遞歸
        @cache
        def dfs(i:int) -> dict[int,int]:
            max_len = {}
            for j in range(i-1, -1, -1):
                d = nums[i] - nums[j]
                if d not in max_len:
                    max_len[d] = dfs(j).get(d,1) + 1
            return max_len
        return max(max(dfs(i).values()) for i in range(1, len(nums)))
        '''
