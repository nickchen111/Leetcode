# TC:O(nlgn) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i

    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res
    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)
class Solution:
    def numTeams(self, rating: List[int]) -> int:
        '''
        也就是要你找遞增三元組 or 遞減三元組有多少個 
        1. python SortedList
        2. BIT
        '''
        n = len(rating)
        # 離散化
        nums = rating.copy()
        nums.sort()
        mp = {x: i + 1 for i, x in enumerate(nums)}  # 離散化 + BIT index 1-based

        bit = FenwickTree(n)
        ans = 0
        for i in range(n):
            idx = mp[rating[i]]
            # 查找有多少數字比我小? bit.pre(idx + 1) 然後判斷一下原本有多少數字比他大 n - bisect_right(nums, rating[i])
            y = bisect_left(nums, rating[i])
            ls = bit.pre(idx - 1) # 代表有 i - ls 的數字比我大 @ 左邊 所以右邊就有 (n - bisect_right(nums, rating[i])) - (i - ls) 比我大
            ll = i - ls
            rl = n - y - 1 - (i - ls)
            rs = y - ls# 右邊比我小的 目前有多少數字比我小 ls 總共有多少數字比我小 bisect_right(nums, rating[i]) -> bisect_right(nums, rating[i]) - ls 就是右邊的量
            ans += ls * rl + ll * rs
            bit.update(idx, 1)
        return ans

        '''
        SortedList
        sl_left = SortedList([rating[0]])
        sl_right = SortedList(rating[i] for i in range(1, n))
        ans = 0
        for i in range(1, n - 1):
            sl_right.remove(rating[i])
            ls = sl_left.bisect_left(rating[i]) 
            ll = len(sl_left) - ls
            rs = sl_right.bisect_left(rating[i])
            rl = len(sl_right) - rs
            ans += ls * rl + ll * rs
            sl_left.add(rating[i])
        return ans
        '''
