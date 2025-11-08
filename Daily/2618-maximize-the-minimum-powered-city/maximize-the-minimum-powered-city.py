class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        n = len(stations)
        arr = [0] * (n + 1)
        for i, p in enumerate(stations):
            mn = max(0, i - r)
            mx = min(len(arr) - 1, i + r + 1)
            arr[mn] += p
            arr[mx] -= p

        def check(mid:int) -> bool:
            cnt = k
            diff_new = arr[:]
            tot = 0
            for i, d in enumerate(diff_new):
                if i == n:
                    return True
                tot += d
                if tot < mid:
                    diff = mid - tot
                    if cnt < diff:
                        return False
                    cnt -= diff
                    tot = mid
                    mx = min(len(diff_new) - 1, i + r + r + 1)
                    diff_new[mx] -= diff
            return True
                
        left = 0
        right = max(arr) + k
        while left < right:
            mid = left + (right - left + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left