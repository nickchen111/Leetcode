class Solution:
    def interactionCosts(self, n: int, edges: list[list[int]], group: list[list[int]]) -> int:
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
        
        # 1. 預處理：DFS 序、深度、倍增法 LCA
        depth = [0] * n
        parent = [[-1] * 20 for _ in range(n)]
        dfn = [0] * n
        timer = 0
        
        stack = [(0, -1, 0)]
        while stack:
            u, p, d = stack.pop()
            dfn[u] = timer
            timer += 1
            depth[u] = d
            parent[u][0] = p
            for v in adj[u]:
                if v != p:
                    stack.append((v, u, d + 1))
        
        # 倍增 LCA 預處理
        for j in range(1, 20):
            for i in range(n):
                if parent[i][j-1] != -1:
                    parent[i][j] = parent[parent[i][j-1]][j-1]
        
        def get_lca(u, v):
            if depth[u] < depth[v]: u, v = v, u
            for j in range(19, -1, -1):
                if depth[u] - (1 << j) >= depth[v]:
                    u = parent[u][j]
            if u == v: return u
            for j in range(19, -1, -1):
                if parent[u][j] != parent[v][j]:
                    u = parent[u][j]
                    v = parent[v][j]
            return parent[u][0]

        # 2. 按組別分類
        groups_map = collections.defaultdict(list)
        for i, g in enumerate(group):
            groups_map[g].append(i)
            
        total_ans = 0
        
        # 3. 對每個組別單獨計算點對距離和
        for g in groups_map:
            nodes = groups_map[g]
            m = len(nodes)
            if m < 2: continue
            
            # 按 DFS 序排序，以便利用單調棧或相鄰 LCA 性質
            nodes.sort(key=lambda x: dfn[x])
            
            # 計算 (|S|-1) * sum(depth)
            sum_depth = sum(depth[u] for u in nodes)
            current_group_dist = (m - 1) * sum_depth
            
            # 計算 2 * sum(depth(LCA(u,v)))
            # 利用性質：sum_{i<j} depth(LCA(v_i, v_j)) 
            # 可以透過單調棧在 O(m) 內算出
            lca_depths = [depth[get_lca(nodes[i], nodes[i+1])] for i in range(m - 1)]
            
            # 這裡使用計算「所有子陣列最小值之和」的技巧
            lca_sum = 0
            stack = [] # (val, count)
            accumulated = 0
            for val in lca_depths:
                count = 1
                while stack and stack[-1][0] >= val:
                    v, c = stack.pop()
                    accumulated -= v * c
                    count += c
                stack.append((val, count))
                accumulated += val * count
                lca_sum += accumulated
                
            total_ans += current_group_dist - 2 * lca_sum
            
        return total_ans