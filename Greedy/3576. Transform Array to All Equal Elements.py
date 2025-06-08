# TC:O(n) SC:O(1)
class Solution:
    def canMakeEqual(self, nums: List[int], k: int) -> bool:
        '''
        問說能否都變成1 or -1
        '''
        n = len(nums)
        def check(target:int) -> bool:
            mul = 1
            left = k
            for i, x in enumerate(nums):
                if x * mul == target:
                    mul = 1
                    continue
                if i == n - 1 or left == 0:
                    return False
                left -= 1
                mul = -1
            return True
        return check(1) or check(-1)

        '''
        #先嘗試能否都變成1
        cntp = 0
        n = len(nums)
        arr1 = nums.copy()
        for i in range(n):
            if i + 1 < n and arr1[i] == -1:
                cntp += 1
                arr1[i + 1] *= -1
            elif i + 1 == n and arr1[i] == -1:
                cntp = inf
            if cntp > k:
                break
        if cntp <= k:
            return True
        cntnp = 0
        for i in range(n):
            if i + 1 < n and nums[i] == 1:
                cntnp += 1
                nums[i + 1] *= -1
            elif i + 1 == n and nums[i] == 1:
                cntnp = inf
            if cntnp > k:
                break
        if cntnp <= k:
            return True
        return False
        '''
