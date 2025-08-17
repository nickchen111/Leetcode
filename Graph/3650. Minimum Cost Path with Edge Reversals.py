# TC:O(n + mlogm) m 為edge數量 SC:O(m + n)
class Solution:
    def minCost(self, n: int, edges: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, 2 * w))
        h = [(0, 0)]
        dis = [inf] * n
        dis[0] = 0

        while h:
            dist, node = heappop(h)
            if dist > dis[node]:
                continue
            if node == n - 1:
                return dist
            for y, wt in g[node]:
                if wt + dist < dis[y]:
                    dis[y] = wt + dist
                    heappush(h, (wt + dist, y))
        return -1
