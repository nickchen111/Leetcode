# 遞歸 如果要寫成遞推可以用set才不會超時 TC:O((n+m)kt) SC:O(nkt) //  Topological Sort + 狀態: TC:O((n+m)kt) SC:O(nkt) // 遞推DP 且更改狀態 只需以edges 遍歷 TC:O(mkt) SC:O(nkt)
class Solution:
    def maxWeight(self, n: int, edges: List[List[int]], k: int, t: int) -> int:
        # 遞推DP 且更改狀態 只需以edges 遍歷 如若要用bitset優化需要用c++
        f = [[set() for _ in range(n)] for _ in range(k + 1)]
        for i in range(n):
            f[0][i].add(0) # 剛開始都可以走0步然後有sum = 0
        for step in range(k): # 走了幾步
            for u, v, w in edges: # 當前節點
                for uw in f[step][u]:
                    if uw + w < t:
                        f[step + 1][v].add(uw + w)
        return max((max(st) for st in f[k] if st), default=-1)
    
        '''
        Topological Sort + 狀態
        graph = [[] for _ in range(n)]
        deg = [0] * n
        for e in edges:
            graph[e[0]].append((e[1], e[2]))
            deg[e[1]] += 1
        f = [[set() for _ in range(k + 1)] for _ in range(n)]
        q = deque(i for i, d in enumerate(deg) if d == 0)
        ans = -1
        while q:
            x = q.popleft()
            f[x][0].add(0) # 這點開始的狀態
            if f[x][k]:
                ans = max(ans, max(f[x][k]))
            for y, w in graph[x]: # 之後要走到的位置與權重
                for i in range(k): # 當前可能走過的edges數
                    for xw in f[x][i]:
                        if xw + w < t:
                            f[y][i + 1].add(xw + w)
                deg[y] -= 1
                if deg[y] == 0:
                    q.append(y)
        return ans
        '''

        '''
        遞歸
        graph = [[] for _ in range(n)]
        for e in edges:
            graph[e[0]].append((e[1], e[2]))
        ans = -1
        @cache
        def dfs(i:int, cnt:int, tot:int) -> None:
            if cnt == k:
                nonlocal ans
                if cnt == k:
                    ans = max(ans, tot)
                return
            for nxt, w in graph[i]:
                if w + tot < t:
                    dfs(nxt, cnt + 1, tot + w)
        for i in range(n):
            dfs(i, 0, 0)
        return ans
        '''
