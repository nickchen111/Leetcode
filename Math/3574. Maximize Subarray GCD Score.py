# TC:O(n * (n + lgU)) SC:O(n) 最優解是logTrick可做到nlgU TC:(n * lgU) SC:O(n + lgU)
class Solution:
    def maxGCDScore(self, nums: List[int], k: int) -> int:
        lowbit_pos = defaultdict(list)

        ans = 0
        intervals = []  # 每个元素是一个三元组 (g, l, r)，表示区间 (l, r] 的 GCD 为 g
        for i, x in enumerate(nums):
            lowbit_pos[x & -x].append(i)

            # 更新已有区间的 GCD
            for p in intervals:
                p[0] = gcd(p[0], x)
            # 添加新元素作为新区间
            intervals.append([x, i - 1, i])

            # 去重（合并 g 相同的区间）
            idx = 1
            for j in range(1, len(intervals)):
                if intervals[j][0] != intervals[j - 1][0]:
                    intervals[idx] = intervals[j]
                    idx += 1
                else:
                    intervals[idx - 1][2] = intervals[j][2]
            del intervals[idx:]

            # 此时我们将区间 [0,i] 划分成了 len(intervals) 个左开右闭区间
            # 对于 intervals 中的 (l,r]，对于任意 j∈(l,r]，gcd(区间[j,i]) 的计算结果均为 g
            for g, l, r in intervals:
                # 不做任何操作
                ans = max(ans, g * (i - l))
                # 看看能否乘 2
                pos = lowbit_pos[g & -g]
                min_l = max(l, pos[-k - 1]) if len(pos) > k else l
                if min_l < r:  # 可以乘 2
                    ans = max(ans, g * 2 * (i - min_l))

        return ans

# 次佳解
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
