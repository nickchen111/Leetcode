# TC:O((n + q)logn) SC:O(nlogn)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1)

    def update(self, i: int, val: int) -> None:
        t = self.tree
        while i < len(t):
            t[i] ^= val
            i += i & -i

    def pre(self, i: int) -> int:
        t = self.tree
        res = 0
        while i > 0:
            res ^= t[i]
            i &= i - 1
        return res


class LcaBinaryLifting:
    def __init__(self, edges: List[List[int]], s: List[int]):
        n = len(edges) + 1
        m = n.bit_length()
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        depth = [0] * n
        pa = [[-1] * n for _ in range(m)]
        tin = [0] * n
        tout = [0] * n
        clock = 0
        path_xor_from_root = [0] * n
        path_xor_from_root[0] = 1 << s[0]

        def dfs(x: int, fa: int) -> None:
            pa[0][x] = fa
            nonlocal clock
            clock += 1
            tin[x] = clock
            for y in g[x]:
                if y != fa:
                    depth[y] = depth[x] + 1
                    path_xor_from_root[y] = path_xor_from_root[x] ^ (1 << s[y])
                    dfs(y, x)
            tout[x] = clock

        dfs(0, -1)

        for i in range(m - 1):
            for x in range(n):
                if (p := pa[i][x]) != -1:
                    pa[i + 1][x] = pa[i][p]

        self.depth = depth
        self.pa = pa
        self.tin = tin
        self.tout = tout
        self.path_xor_from_root = path_xor_from_root

    def get_kth_ancestor(self, node: int, k: int) -> int:
        pa = self.pa
        for i in range(k.bit_length()):
            if k >> i & 1:
                node = pa[i][node]
                if node < 0:
                    return -1
        return node

    def get_lca(self, x: int, y: int) -> int:
        if self.depth[x] > self.depth[y]:
            x, y = y, x
        y = self.get_kth_ancestor(y, self.depth[y] - self.depth[x])
        if y == x:
            return x
        pa = self.pa
        for i in range(len(pa) - 1, -1, -1):
            px, py = pa[i][x], pa[i][y]
            if px != py:
                x, y = px, py
        return pa[0][x]


class Solution:
    def palindromePath(self, n: int, edges: list[list[int]], s: str, queries: list[str]) -> list[bool]:
        ord_a = ord('a')
        t = [ord(ch) - ord_a for ch in s]  # 映射成 [0, 25] 中的整數

        g = LcaBinaryLifting(edges, t)
        tin = g.tin
        tout = g.tout
        path_xor_from_root = g.path_xor_from_root

        f = FenwickTree(n)
        ans = []

        for q in queries:
            op, x, y = q.split()
            x = int(x)
            if op[0] == 'u':
                c = ord(y) - ord_a
                val = (1 << t[x]) ^ (1 << c)
                t[x] = c
                f.update(tin[x], val)
                f.update(tout[x] + 1, val)
            else:
                y = int(y)
                lca = g.get_lca(x, y)
                res = path_xor_from_root[x] ^ path_xor_from_root[y] ^ f.pre(tin[x]) ^ f.pre(tin[y]) ^ (1 << t[lca])
                ans.append(res & (res - 1) == 0)

        return ans
