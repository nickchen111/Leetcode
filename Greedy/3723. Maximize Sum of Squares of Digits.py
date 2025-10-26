# TC:O(sum // 9) SC:O(1)
class Solution:
    def maxSumOfSquares(self, num: int, sum: int) -> str:
        if num * 9 < sum:
            return ""
        ans = []
        for i in range(num):
            tmp = min(9, sum)
            ans.append(str(tmp))
            sum -= tmp
        if sum != 0:
            return ""
        return "".join(ans)
