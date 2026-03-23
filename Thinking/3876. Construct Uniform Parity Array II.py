# TC:O(n) SC:O(1)
class Solution:
    def uniformArray(self, nums1: list[int]) -> bool:
        '''
        就是看是否有一個比自己小的數字並且看說該數字會是odd or even
        假設要創odd -> 遇到偶數 就要找odd 相減
        創建even -> 遇到odd 也要找odd 相減
        '''
        mn = inf
        for x in nums1:
            if x % 2:
                mn = min(mn, x)
        if mn == inf: # 都是偶數
            return True

        for x in nums1:
            if x % 2 == 0 and x <= mn:
                return False
        return True
