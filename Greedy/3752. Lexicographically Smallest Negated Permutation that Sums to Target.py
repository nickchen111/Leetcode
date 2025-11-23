# TC:O(n) SC:O(1)
class Solution:
    def lexSmallestNegatedPerm(self, n: int, target: int) -> List[int]:
        tot = n * (n + 1) // 2
        if target > tot or target < -tot or target % 2 != tot % 2:
            return []
        ans = [0] * n
        cur = 0
        l = 0
        r = n - 1
        for i in range(n, 0, -1):
            left = i * (i - 1) // 2
            if cur + left - i >= target and cur - left - i <= target:
                ans[l] = -i
                l += 1
                cur -= i
            else:
                ans[r] = i
                r -= 1
                cur += i
        return ans
