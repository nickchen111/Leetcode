# TC:O(n + mlogm) SC:O(n + m)
class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for u, v, start, end in edges:
            g[u].append((v, start, end))
        dist = [inf] * n
        pq = [(0,0)] # cost, 當下node
        while pq:
            dx, x = heappop(pq)
            if dx > dist[x]:
                continue
            dist[x] = dx
            if x == n - 1:
                return dx
            for y, start, end in g[x]:
                new_dis = max(dx, start) + 1
                if new_dis - 1 <= end and new_dis < dist[y]:
                    heappush(pq, (new_dis, y))
        return -1
