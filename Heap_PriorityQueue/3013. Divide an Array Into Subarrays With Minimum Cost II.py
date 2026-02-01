# TC:O(nlogdist) SC:O(dist)
class Solution:
    def minimumCost(self, nums: List[int], k: int, dist: int) -> int:
        '''
        就是在一個固定範圍內選k-1個數字 盡量小的選
        需要一個資料結構去選出k-1個數字然後用這些數字計算出總和
        j - i + 1 <= dist 在這之中去選出k - 1個
        '''
        n = len(nums)

        sl_min = SortedList()
        sl_max = SortedList()

        tot = 0
        ans = inf

        for j in range(1, n):
            x = nums[j]
            if len(sl_min) < k - 1:
                sl_min.add(x)
                tot += x
            elif x < sl_min[-1]:
                y = sl_min.pop()
                tot -= y
                sl_max.add(y)

                sl_min.add(x)
                tot += x
            else:
                sl_max.add(x)

            if len(sl_min) == k - 1:
                ans = min(ans, tot + nums[0])

            if j >= dist + 1:
                delete = nums[j - dist]

                idx = bisect_left(sl_max, delete)
                if idx < len(sl_max) and sl_max[idx] == delete:
                    sl_max.pop(idx)
                else:
                    idx = bisect_left(sl_min, delete)
                    sl_min.pop(idx)
                    tot -= delete
                    if sl_max:
                        y = sl_max.pop(0)
                        sl_min.add(y)
                        tot += y
        return ans
