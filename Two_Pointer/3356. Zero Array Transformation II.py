# Binary Search: TC:O((n + q)lgn) SC:O(n) Two Pointer: TC:O(n + q) SC:O(n) Segment Tree: TC:O(n + qlgn) SC:O(n)
class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        '''
        改成最多可以扣val 每個index 可以隨意
        求最少可以扣多少次讓他變成0 越多肯定越容易 有單調性 -> 二分
        方法2:
        雙指針 走到某個點的時候判斷一下當下的cur_sum 如若無法降低到合法狀態 就繼續走query
        方法3:
        直接用lazy 線段樹模擬區間減法 等到區間最大值 <= 0 就是答案
        '''
        # 雙指針
        n = len(nums)
        m = len(queries)
        diff = [0] * (n + 1)
        sum_d = k = 0
        for i, (x, d) in enumerate(zip(nums, diff)):
            sum_d += d
            while k < m and sum_d < x:
                l, r, val = queries[k]
                diff[l] += val
                diff[r + 1] -= val
                if l <= i <= r:
                    sum_d += val
                k += 1
            if sum_d < x:
                return -1
        return k

        '''
        lazy 線段樹模擬區間減法
        n = len(nums)
        m = 2 << n.bit_length()
        mx = [0] * m
        todo = [0] * m

        def do(o: int, v: int) -> None:
            mx[o] -= v
            todo[o] += v

        def spread(o: int) -> None:
            if todo[o] != 0:
                do(o * 2, todo[o])
                do(o * 2 + 1, todo[o])
                todo[o] = 0

        def maintain(o: int) -> None:
            mx[o] = max(mx[o * 2], mx[o * 2 + 1])

        def build(o: int, l: int, r: int) -> None:
            if l == r:
                mx[o] = nums[l]
                return
            m = (l + r) // 2
            build(o * 2, l, m)
            build(o * 2 + 1, m + 1, r)
            maintain(o)

        def update(o: int, l: int, r: int, ql: int, qr: int, v: int) -> None:
            if ql <= l and r <= qr:
                do(o, v)
                return
            spread(o)
            m = (l + r) // 2
            if ql <= m:
                update(o * 2, l, m, ql, qr, v)
            if m < qr:
                update(o * 2 + 1, m + 1, r, ql, qr, v)
            maintain(o)

        build(1, 0, n - 1)
        if mx[1] <= 0:
            return 0

        for i, (ql, qr, v) in enumerate(queries):
            update(1, 0, n - 1, ql, qr, v)
            if mx[1] <= 0:
                return i + 1
        return -1
        '''

        '''
        二分 + Diff
        left, right = 0, m
        def check(mid : int) -> bool:
            diff = [0] * (n + 1)
            for i in range(mid):
                diff[queries[i][0]] += queries[i][2]
                diff[queries[i][1] + 1] -= queries[i][2]
            cur_sum = 0
            for i in range(n):
                cur_sum += diff[i]
                if nums[i] - cur_sum > 0:
                    return False
            return True
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return left if check(left) else -1
        '''
