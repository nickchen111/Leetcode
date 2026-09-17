class Solution:
    def minSumOfLengths(self, arr: list[int], target: int) -> int:
        n = len(arr)
        s = l = 0
        pre_min = [inf] * (n + 1)
        min_len = ans = inf
        for r in range(n):
            s += arr[r]

            while s > target:
                s -= arr[l]
                l += 1
            
            if s == target:
                min_len = min(min_len, r - l + 1)
                ans = min(ans, pre_min[l] + r - l + 1)
            pre_min[r + 1] = min_len
        return ans if ans != inf else -1