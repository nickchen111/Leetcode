# TC:O(n * n * lgU) SC:O(n)
# TC:O(n * (n + lgU)) SC:O(n) 最優解是logTrick可做到nlgU
def cnt_2(x:int) -> int:
    cnt = 0
    while x & 1 == 0:
        cnt += 1
        x >>= 1
    return cnt
class Solution:
    def maxGCDScore(self, nums: List[int], k: int) -> int:
        '''
        可以任意挑選一個數字 * 2 每個數字最多一次
        問說做完最多k次操作後
        n = 1500 k = 1500 大概可以允許n * k時間 * lgU 也是可以的
        我可以求出每段subarray的最大公因數?! 越長的array代表gcd可能越小
        gcd 枚舉?!
        思路上來說 在k範圍內的元素我都可以去計算看看他的subarray最大值 就直接乘上2
        超過的話k就不起作用惹
        '''
        n = len(nums)
        # div_2 = [cnt_2(x) for x in nums]
        ans = 0
        for i in range(n):
            g = lowbit_cnt = 0
            lowbit_min = inf
            for j in range(i, n):
                g = gcd(g, nums[j])
                lb = nums[j] & -nums[j]
                if lb < lowbit_min:
                    lowbit_cnt = 1
                    lowbit_min = lb
                elif lowbit_min == lb:
                    lowbit_cnt += 1
                if lowbit_cnt <= k:
                    ans = max(ans, g * 2 * (j - i + 1))
                else:
                    ans = max(ans, g * (j - i + 1))
        return ans
