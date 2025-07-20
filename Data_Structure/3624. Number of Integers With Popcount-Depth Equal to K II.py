# TC:O((n + q) * logn) SC:O(n)
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
    def popcountDepth(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        max_depth = 6
        def get_depth(x):
            depth = 0
            while x != 1:
                x = bin(x).count('1')
                depth += 1
            return depth
        fws = [FenwickTree(n) for _ in range(max_depth)]
     
        index_depth = [0] * n
        
        for i in range(n):
            d = get_depth(nums[i])
            index_depth[i] = d
            fws[d].update(i + 1, 1)

        res = []
        for q in queries:
            if q[0] == 1:
                _, l, r, k = q
                res.append(fws[k].query(l + 1, r + 1))
            else:
                _, idx, val = q
                old_depth = index_depth[idx]
                new_depth = get_depth(val)
                if old_depth != new_depth:
                    fws[old_depth].update(idx + 1, -1)
                    fws[new_depth].update(idx + 1, 1)
                    index_depth[idx] = new_depth
                nums[idx] = val
        return res
