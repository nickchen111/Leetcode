class Solution:
    def maxBalancedShipments(self, nums: List[int]) -> int:
        '''
        求有多少個遞減段
        4 5 4 5 4 5 4
        '''
        n = len(nums)
        i = 1
        ans = 0
        while i < n:
            if nums[i] < nums[i - 1]:
                ans += 1
                i += 2
                continue
            i += 1
        return ans

        '''
        i = ans = 0
        while i < n:
            j = i + 1
            while j < n and nums[j] >= nums[j - 1]:
                j += 1
            if j < n: ans += 1
            i = j + 1
        return ans
        '''