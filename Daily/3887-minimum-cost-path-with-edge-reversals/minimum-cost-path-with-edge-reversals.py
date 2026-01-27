class Solution:
    def minCost(self, n: int, edges: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, 2*w))
        dist = [inf] * n
        dist[0] = 0
        h = [(0,0)]
        while h:
            dis, node = heappop(h)
            if dis > dist[node]:
                continue
            if node == n - 1:
                return dis
            for y, wt in g[node]:
                if wt + dis < dist[y]:
                    dist[y] = wt + dis
                    heappush(h, (wt + dis, y))
        return -1
            