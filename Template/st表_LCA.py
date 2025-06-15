# 包進class內
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

    # 返回 x 和 y 的最近公共祖先
    def get_lca(self, x: int, y: int) -> int:
        if self.depth[x] > self.depth[y]:
            x, y = y, x
        # 使 y 和 x 在同一深度
        y = self.get_kth_ancestor(y, self.depth[y] - self.depth[x])
        if y == x:
            return x
        for i in range(self.m - 1, -1, -1):
            px, py = self.pa[x][i], self.pa[y][i]
            if px != py:
                x, y = px, py  # 同时往上跳 2**i 步
        return self.pa[x][0]

    # 返回 x 到 y 的距离（最短路长度）
    def get_dis(self, x: int, y: int) -> int:
        return self.dis[x] + self.dis[y] - self.dis[self.get_lca(x, y)] * 2

    # 从 x 往上跳【至多】d 距离，返回最远能到达的节点
    def upto_dis(self, x: int, d: int) -> int:
        dx = self.dis[x]
        for i in range(self.m - 1, -1, -1):
            p = self.pa[x][i]
            if p != -1 and dx - self.dis[p] <= d:  # 可以跳至多 d
                x = p
        return x

# 寫在main上
n = len(edges) + 1
LOG = n.bit_length()
tree = defaultdict(list) # tree = [[] for _ in range(n + 1)]
for u, v, w in edges:
    tree[u].append((v, w))
    tree[v].append((u, w))

stjump = [[-1] * LOG for _ in range(n)]
deep = [0] * n
dist = [0] * n  # dist[i] = distance from root to i

def dfs(u, p):
    for v, w in tree[u]:
        if v == p:
            continue
        deep[v] = deep[u] + 1
        stjump[v][0] = u
        dist[v] = dist[u] + w
        dfs(v, u)
dfs(0, -1)
for j in range(1, LOG):
    for i in range(n):
        if stjump[i][j - 1] != -1:
            stjump[i][j] = stjump[stjump[i][j - 1]][j - 1]

def lca(u, v):
    if deep[u] < deep[v]:
        u, v = v, u
    for j in range(LOG - 1, -1, -1):
        if stjump[u][j] != -1 and deep[stjump[u][j]] >= deep[v]:
            u = stjump[u][j]
    if u == v:
        return u
    for j in range(LOG - 1, -1, -1):
        if stjump[u][j] != -1 and stjump[u][j] != stjump[v][j]:
            u = stjump[u][j]
            v = stjump[v][j]
    return stjump[u][0]
def path_dist(x:int, y:int, anc:int) -> int:
    return dist[x] + dist[y] - 2 * dist[anc]
