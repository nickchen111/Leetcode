class Solution:
    def countGoodSubarrays(self, nums: list[int]) -> int:
        '''
        OR 只會變大
        每個位置 判斷一下目前的bit 之前的都包含 然後看包含的範圍到哪
        越短可能越合法?! 不一定 可以突然出現一個都包含的數字
        所以應該是去記錄目前這個點位 之前出現的最古早位置在哪
        感覺很像貢獻法
        '''
        last = {}
        ans = 0
        or_left = [] # (子樹組or值, 最小左端點)

        for i, x in enumerate(nums):
            last[x] = i
            # 先將原本or_left array加上這次結果
            for p in or_left:
                p[0] |= x
            or_left.append([x, i])
            # 原地去重
            idx = 1
            for j in range(1, len(or_left)):
                if or_left[j][0] != or_left[j - 1][0]:
                    or_left[idx] = or_left[j]
                    idx += 1
            del or_left[idx:]

            for k, (or_val, left) in enumerate(or_left):
                right = or_left[k + 1][1] - 1 if k < len(or_left) - 1 else i
                j = last.get(or_val, -1)
                if j >= left:
                    ans += min(right, j) - left + 1
        return ans



        '''
        n = len(nums)
        L, R = [0] * n, [n - 1] * n
        last_bit = [-1] * 31
        last_val = {}
        for i, v in enumerate(nums):
            bound = -1
            for b in range(31):
                if not (v & (1 << b)):
                    bound = max(bound, last_bit[b])
                else:
                    last_bit[b] = i
            
            if v in last_val:
                bound = max(bound, last_val[v])
            L[i] = bound + 1
            last_val[v] = i

        next_bit = [n] * 31
        for i in range(n - 1, -1, -1):
            v = nums[i]
            bound = n
            for b in range(31):
                if not (v & (1 << b)):
                    bound = min(bound, next_bit[b])
                else:
                    next_bit[b] = i
            R[i] = bound - 1

        ans = 0
        for i in range(n):
            ans += (i - L[i] + 1) * (R[i] - i + 1)
        return ans
        '''