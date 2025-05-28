# TC:O(n*k + m*k) SC:O(n + m)
class Solution:
    def build_tree(self, edges: List[List[int]], k: int) -> Callable[[int, int, int], int]:
        g = [[] for _ in range(len(edges) + 1)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        def dfs(x: int, fa: int, d: int) -> int:
            if d > k:
                return 0
            cnt = 1
            for y in g[x]:
                if y != fa:
                    cnt += dfs(y, x, d + 1)
            return cnt
        return dfs

    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]], k: int) -> List[int]:
        max2 = 0
        if k:
            dfs = self.build_tree(edges2, k - 1)
            max2 = max(dfs(i, -1, 0) for i in range(len(edges2) + 1))

        dfs = self.build_tree(edges1, k)
        return [dfs(i, -1, 0) + max2 for i in range(len(edges1) + 1)]



        
