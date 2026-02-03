class Solution:
    def isTrionic(self, nums: List[int]) -> bool:
        n = len(nums)
        cnt = 0
        idx = 0
        def check() -> bool:
            nonlocal cnt
            nonlocal idx
            ori = idx
            neg = -1 if cnt % 2 else 1
            while idx + 1 < n:
                if nums[idx + 1] * neg > nums[idx] * neg:
                    idx += 1
                else:
                    break
            cnt += 1 if idx - ori + 1 > 1 else 0
            # print(ori, idx, cnt)
            return True if idx - ori + 1 > 1 else False
        if not check():
            return False
        if not check():
            return False
        if not check():
            return False
        return True if idx == n - 1 else False

        
