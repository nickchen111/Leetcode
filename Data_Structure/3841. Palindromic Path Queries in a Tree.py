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


# 
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1)

    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] ^= val
            i += i & -i

    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res ^= self.tree[i]
            i &= i - 1
        return res

    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) ^ self.pre(l - 1)


class LcaBinaryLifting:
    def __init__(self, edges: List[List[int]]):
        n = len(edges) + 1
        self.m = m = n.bit_length()
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, w))

        depth = [0] * n
        dis = [0] * n
        pa = [[-1] * m for _ in range(n)]

        def dfs(x: int, fa: int) -> None:
            pa[x][0] = fa
            for y, w in g[x]:
                if y != fa:
                    depth[y] = depth[x] + 1
                    dis[y] = dis[x] + w
                    dfs(y, x)

        dfs(0, -1)

        for i in range(m - 1):
            for x in range(n):
                if (p := pa[x][i]) != -1:
                    pa[x][i + 1] = pa[p][i]

        self.depth = depth
        self.dis = dis
        self.pa = pa

    def get_kth_ancestor(self, node: int, k: int) -> int:
        for i in range(k.bit_length()):
            if k >> i & 1:
                node = self.pa[node][i]
        return node

    def get_lca(self, x: int, y: int) -> int:
        if self.depth[x] > self.depth[y]:
            x, y = y, x
        y = self.get_kth_ancestor(y, self.depth[y] - self.depth[x])
        if y == x:
            return x
        for i in range(self.m - 1, -1, -1):
            px, py = self.pa[x][i], self.pa[y][i]
            if px != py:
                x, y = px, py
        return self.pa[x][0]

    def get_dis(self, x: int, y: int) -> int:
        return self.dis[x] + self.dis[y] - self.dis[self.get_lca(x, y)] * 2

    def upto_dis(self, x: int, d: int) -> int:
        dx = self.dis[x]
        for i in range(self.m - 1, -1, -1):
            p = self.pa[x][i]
            if p != -1 and dx - self.dis[p] <= d:
                x = p
        return x


class Solution:
    def palindromePath(self, n: int, edges: list[list[int]], s: str, queries: list[str]) -> list[bool]:
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        tin = [0] * n
        tout = [0] * n
        clock = 0

        def dfs(u: int, p: int):
            nonlocal clock
            clock  += 1
            tin[u] = clock
            for v in g[u]:
                if v == p:
                    continue
                dfs(v, u)
            tout[u] = clock

        dfs(0, -1)

        ledges = []
        for u, v in edges:
            ledges.append([u, v, 0])
        lca = LcaBinaryLifting(ledges)

        bit = FenwickTree(n + 2)
        cur = [1 << (ord(c) - 97) for c in s]

        def range_xor(l, r, val):
            bit.update(l, val)
            bit.update(r + 1, val)

        for i in range(n):
            range_xor(tin[i], tout[i], cur[i])

        ans = []
        for q in queries:
            sp = q.split()
            if sp[0] == "update":
                u = int(sp[1])
                new_mask = 1 << (ord(sp[2]) - ord('a'))
                diff = cur[u] ^ new_mask
                if diff:
                    range_xor(tin[u], tout[u], diff)
                    cur[u] = new_mask
            else:
                a = int(sp[1])
                b = int(sp[2])
                L = lca.get_lca(a, b)
                mask = bit.pre(tin[a]) ^ bit.pre(tin[b]) ^ cur[L]
                ans.append(mask == 0 or (mask & (mask - 1)) == 0)
        return ans
