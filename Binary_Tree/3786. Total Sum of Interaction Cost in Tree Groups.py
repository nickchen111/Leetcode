# TC:O(nU) SC:O(n + U)
class Solution:
    def interactionCosts(self, n: int, edges: List[List[int]], group: List[int]) -> int:
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)
        
        total = Counter(group)
        ans = 0
        def dfs(x:int, fa:int) -> defaultdict:
            nonlocal ans
            cnt_x = defaultdict(int)
            cnt_x[group[x]] = 1
            for y in g[x]:
                if y == fa:
                    continue
                cnt_y = dfs(y, x)
                for i, c in cnt_y.items():
                    ans += c * (total[i] - c)
                    cnt_x[i] += c
            return cnt_x
        dfs(0, -1)
        return ans

