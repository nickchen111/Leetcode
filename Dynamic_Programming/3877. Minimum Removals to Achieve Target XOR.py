# TC:O(nU) U = max(nums) SC:O(nU)
class Solution:
    def minRemovals(self, nums: List[int], target: int) -> int:
        '''
        最少需要移除多少個數字 讓XOR 結果 = target 需要挑出最長的subsequence
        選了前面i個數字 能夠組出 j 數字的選擇最多的數字量是多少?
        類似背包！？
        '''
        @cache
        def dfs(i : int, cur_num : int) -> int:
            if i < 0:
                return 0 if cur_num == target else -inf
            return max(dfs(i - 1, cur_num), dfs(i - 1, cur_num ^ nums[i]) + 1)
        mx = dfs(len(nums) - 1, 0)
        return len(nums) - mx if mx != -inf else -1
        
