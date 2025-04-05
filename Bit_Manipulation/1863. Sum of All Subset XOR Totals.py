# TC:O(n) SC:O(n)
class Solution:
    def subsetXORSum(self, nums: List[int]) -> int:
        n = len(nums)
        # OR做法
        '''
        只要在某一位上有1，那麼可以證明他就有2^ n - 1次方種可能讓他維持是1
        想像其他n-1個數 選偶數個1 放到當前是1的集合 得出答案會是 1
        n-1個數 選奇數個1 不放當前1的集合 得出答案也是1 所以會有2^(n-1)答案
        那麼要如何判斷每個位置是否有1 -> OR
        '''
        ans = 0
        for x in nums:
            ans |= x
        return ans << (n - 1)
        '''
        Backtrack做法 2^n
        def dfs(i:int, total:int) -> int:
            if i == n: return total
            return dfs(i+1, total) + dfs(i+1, total ^ nums[i])
        return dfs(0, 0)
        '''
        '''
        Mask 做法
        submask = mask = (1 << n) - 1
        ans = 0
        # n * 2 ^ n
        while submask:
            cur_mask = submask
            cnt = cur = 0
            while (cur_mask >> cnt):
                if cur_mask >> cnt & 1:
                    cur ^= nums[n - cnt - 1]
                cnt += 1
            ans += cur
            submask = (submask - 1) & mask
        return ans
        '''
