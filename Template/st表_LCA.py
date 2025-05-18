tree = defaultdict(list)
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
