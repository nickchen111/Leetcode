# TC:O(n) SC:O(n)
class Solution:
    def minIncrease(self, n: int, edges: List[List[int]], cost: List[int]) -> int:
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        graph[0].append(-1)
        ans = 0
        def dfs(u:int, pa:int, path_sum:int) -> int:
            """
            返回從當前節點到葉節點的最大路徑成本
            同時計算需要增加成本的節點數量
            """
            path_sum += cost[u]
            if len(graph[u]) == 1: return path_sum
            max_s = cnt = 0
            for nxt in graph[u]:
                if nxt != pa:
                    mx = dfs(nxt, u, path_sum)
                    if mx > max_s:
                        cnt = 1
                        max_s = mx
                    elif mx == max_s:
                        cnt += 1
            nonlocal ans
            ans += len(graph[u]) - cnt - 1
            return max_s
        dfs(0, -1, 0)
        return ans
