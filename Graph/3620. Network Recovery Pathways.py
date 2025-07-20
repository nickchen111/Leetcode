# TC:O(ElogElogU) SC:O(E)
class Solution:
    def findMaxPathScore(self, edges: List[List[int]], online: List[bool], k: int) -> int:
        n = len(online)
        valid_edges = [(u, v, cost) for u, v, cost in edges if online[u] and online[v]]
        if not valid_edges:
            return -1

        def check(min_cost: int) -> bool:
            g = [[] for _ in range(n)]
            for u, v, cost in valid_edges:
                if cost >= min_cost:
                    g[u].append((v, cost))
            dist = [float('inf')] * n
            dist[0] = 0
            heap = [(0, 0)]  # (acc_cost, node)
            while heap:
                acc, u = heappop(heap)
                if u == n - 1:
                    return True
                if acc > dist[u]:
                    continue
                for v, cost in g[u]:
                    if acc + cost < dist[v]:
                        dist[v] = acc + cost
                        if dist[v] <= k:
                            heappush(heap, (dist[v], v))
            return False

        left, right = 0, max(cost for _, _, cost in valid_edges)
        while left < right:
            mid = (left + right + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left if check(left) else -1
