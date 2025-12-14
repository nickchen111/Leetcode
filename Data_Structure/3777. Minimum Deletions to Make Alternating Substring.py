# TC:O((n + q)* logn) SC:O(n)
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
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        s = list(s)
        bit = FenwickTree(n)
        for i in range(n - 1):
            if s[i] != s[i + 1]:
                bit.update(i + 1, 1)
        ans = []
        for q in queries:
            if q[0] == 1:
                j = q[1]
                new_char = 'B' if s[j] == 'A' else 'A'
                if j > 0:
                    bit.update(j, -1 if s[j - 1] != s[j] else 1)
                if j < n - 1:
                    bit.update(j + 1, -1 if s[j + 1] != s[j] else 1)
                s[j] = new_char
            else:
                l, r = q[1], q[2]
                length = r - l + 1
                if l == r:
                    ans.append(0)
                else:
                    changes = bit.pre(r) - bit.pre(l)
                    segments = 1 + changes
                    ans.append(length - segments)
        return ans
