# TC:O(n) SC:O(U) U為數字種類
class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        '''
        就是看一開始有多少數字比k大 如果有比k小的就無法達成
        '''
        if min(nums) < k:
            return -1
        return len(set(nums)) + (min(nums) > k) - 1
