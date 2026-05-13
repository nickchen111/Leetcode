class Solution:
    def minMoves(self, nums: List[int], limit: int) -> int:
        n = len(nums)
        diff = [0] * (limit * 2 + 2)

        for i in range(n // 2):
            x = nums[i]
            y = nums[-1 - i]
            l = min(x, y) + 1
            r = max(x, y) + limit

            # [2, l-1] += 2
            diff[2] += 2
            diff[l] -= 2

            # [l, r] += 1
            diff[l] += 1
            diff[r + 1] -= 1

            # x+y 实际操作 0 次，从 [l, r] 中去掉
            # [x+y, x+y] -= 1
            diff[x + y] -= 1
            diff[x + y + 1] += 1

            # [r+1, limit*2] += 2
            diff[r + 1] += 2
            # limit*2+1 不在 [2, limit*2] 中，可以省略

        ans = inf
        sum_d = 0
        for d in diff[2 : limit * 2 + 1]:
            sum_d += d
            ans = min(ans, sum_d)
        return ans
