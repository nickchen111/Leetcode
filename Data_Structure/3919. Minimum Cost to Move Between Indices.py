# TC:O(n) SC:O(n)
class Solution:
    def minCost(self, nums: list[int], queries: list[list[int]]) -> list[int]:
        '''
        因為nums 是嚴格遞增 所以盡量能closet 往前多走一點總是更好的
        不能的時候就走最短的方式跳到下一個可以使用closet的點
        可以用dp來解
        '''
        n = len(nums)
        dp_r = [inf] * n
        dp_r[-1] = 0
        closet = [-1] * n
        closet[0] = 1
        closet[-1] = n - 2
        for i in range(1, n - 1):
            closet[i] = i - 1 if nums[i] - nums[i - 1] <= nums[i + 1] - nums[i] else i + 1
        for i in range(n - 2, -1, -1):
            dp_r [i] = dp_r [i + 1] + 1 if closet[i] == i + 1 else dp_r [i + 1] + nums[i + 1] - nums[i]
        dp_l = [inf] * n
        dp_l[0] = 0
        # print(closet)
        for i in range(1, n):
            dp_l[i] = dp_l[i - 1] + 1 if closet[i] == i - 1 else dp_l[i - 1] + nums[i] - nums[i - 1]
        ans = [0] * len(queries)
        for i, q in enumerate(queries):
            l, r = q
            if l > r: # 往左走
                ans[i] = dp_l[l] - dp_l[r]
            else:
                ans[i] = dp_r[l] - dp_r[r]
        return ans
                
        
