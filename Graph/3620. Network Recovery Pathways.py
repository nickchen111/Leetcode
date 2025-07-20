# DP TC:O((n + m) * logU) 其中 n 是 online 的長度，m 是 edges 的長度 U 為邊權最大值 SC:O(n + m)
class Solution:
    def findMaxPathScore(self, edges: List[List[int]], online: List[bool], k: int) -> int:
        n = len(online)
        g = [[] for _ in range(n)]
        max_wt = 0
        for u, v, cost in edges:
            if online[u] and online[v]:
                g[u].append((v, cost))
                max_wt = max(max_wt, cost)

        def check(min_cost: int) -> bool:
            @cache
            def dfs(x:int) -> int:
                if x == n - 1:
                    return 0
                ans = inf
                for y, cost in g[x]:
                    if cost >= min_cost:
                        ans = min(ans, dfs(y) + cost)
                return ans
            return dfs(0) <= k

        left, right = -1, max_wt
        while left < right:
            mid = (left + right + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left

# Dijkstra TC:O((n+m)logmlogU) SC:O(n + m)
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
