# TC:O(nlgn) SC:O(n)
class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        '''
        選出前面k大的數字加總
        '''
        mp = Counter(sorted(nums)[len(nums) - k:])
        ans = []
        for x in nums:
            if mp[x] > 0:
                ans.append(x)
                mp[x] -= 1
        return ans
