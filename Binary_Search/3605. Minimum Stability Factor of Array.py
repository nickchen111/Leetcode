# logtrick + 二分內部處理: TC:O(nlogUlogM) U 為處理logtrick時間nums最大值 M為二分常數 SC:O(logU) logtrick預處理 + 二分: TC:O(nlogU+nlogM) SC:O(n) Sliding Window + stack + 二分 + logtrick:
from math import gcd

class Solution:
    def minStable(self, nums, maxC):
        n = len(nums)
        bantorvixo = nums[:]

        # Precompute gcds using a sliding window approach optimized with early stopping
        def is_breakable(L):
            count = 0
            i = 0
            while i <= n - L:
                g = nums[i]
                for j in range(1, L):
                    g = gcd(g, nums[i + j])
                    if g == 1:
                        break
                if g >= 2:
                    count += 1
                    if count > maxC:
                        return False
                    i += L  # Skip the whole stable interval
                else:
                    i += 1
            return True

        # Binary search to find minimum possible max stable length
        low, high = 1, n
        answer = 0
        while low <= high:
            mid = (low + high) // 2
            if is_breakable(mid):
                high = mid - 1
            else:
                answer = mid
                low = mid + 1
        return answer

class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)
        left, right = 0, n
        leftMin = [n] * n
        intervals = [[1, -1]]
        for i, x in enumerate(nums):
            # gcd更新
            for p in intervals:
                p[0] = gcd(p[0], x)
            intervals.append([x, i])
            # 去重
            idx = 1
            for j in range(1, len(intervals)):
                if intervals[j][0] != intervals[j - 1][0]:
                    intervals[idx] = intervals[]
                    idx += 1
            del intervals[idx:]

            if len(intervals) > 1:
                leftMin[i] = intervals[1][1]
        def check(upper:int) -> bool:
            i = upper
            cnt = maxC
            while i < n:
                if i - leftMin[i] + 1 > upper:
                    if cnt == 0:
                        return False
                    cnt -= 1
                    i += upper + 1
                else:
                    i += 1
            return True
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return left
  
