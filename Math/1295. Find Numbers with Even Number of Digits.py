# TC:O(n * m) m 為數字平均長度 SC:O(1)
class Solution:
    def findNumbers(self, nums: List[int]) -> int:
        '''
        問說一個數字是幾位數? 是否是偶數
        '''
        b = 10
        def trans(num:int) -> int:
            cnt = 0
            while num:
                num, r = divmod(num, b)
                cnt += 1
            return cnt
        ans = 0
        for x in nums:
            if trans(x) % 2 == 0:
                ans += 1
        return ans
