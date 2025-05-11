# TC:O(n * k) SC:O(n * k)
class Solution:
    def subtreeInversionSum(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        graph = [[] for _ in range(len(nums))]
        for e in edges:
            graph[e[0]].append(e[1])
            graph[e[1]].append(e[0])
        memo = {}
        def dfs(u:int, fa:int, cd:int, mul:int) -> int:
            t = (u, cd, mul)
            if t in memo:
                return memo[t]
            ans = nums[u] * mul
            # 不翻轉
            for nxt in graph[u]:
                if nxt != fa:
                    ans += dfs(nxt, u, cd - 1 if cd else 0, mul)
            if cd == 0: # 可翻轉
                ret = nums[u] * mul * -1
                for nxt in graph[u]:
                    if nxt != fa:
                        ret += dfs(nxt, u, k - 1, mul * -1)
                if ret > ans:
                    ans = ret
            memo[t] = ans
            return ans
        return dfs(0, -1, 0, 1)
        
