# logtrick + 二分內部處理: TC:O(nlogUlogM) U 為處理logtrick時間nums最大值 M為二分常數 SC:O(logU) logtrick預處理 + 二分: TC:O(nlogU+nlogM) SC:O(n) Sliding Window + stack + 二分 + logtrick: TC: O(nlogU+nlogM) SC:O(n)
class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        left, right = 0, len(nums)
        def check(upper:int) -> bool:
            cnt = maxC
            intervals = [] # [gcd, 最小左端點]
            for i, x in enumerate(nums):
                # 先去將gcd更新
                for p in intervals:
                    p[0] = gcd(p[0], x)
                intervals.append([x, i])
                # 去重更新
                idx = 1
                for j in range(1, len(intervals)):
                    if intervals[j][0] != intervals[j - 1][0]:
                        intervals[idx] = intervals[j]
                        idx += 1
                del intervals[idx:]
                # 判斷是否有違法的
                if intervals[0][0] == 1:
                    intervals.pop(0)
                if intervals and i - intervals[0][1] + 1 > upper:
                    if cnt == 0:
                        return False
                    cnt -= 1
                    intervals.clear()
            return True
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return left

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

class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)
        l, r = 0, n
        leftMin = [n] * n
        left = bottom = right_gcd = 0
        for right, x in enumerate(nums):
            right_gcd = gcd(right_gcd, x)
            while left <= right and (gcd(right_gcd, nums[left]) == 1):
                left += 1
                if bottom < left:
                    for i in range(right - 1, left - 1, -1):
                        nums[i] = gcd(nums[i], nums[i + 1])
                    bottom = right
                    right_gcd = 0
            leftMin[right] = left
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
        while l < r:
            mid = (l + r) // 2
            if check(mid):
                r = mid
            else:
                l = mid + 1
        return l
