# TC:O((n + m) * cnt) max (cnt) = 26 SC:O(n * cnt + m)
class Solution:
    def largestPathValue(self, colors: str, edges: List[List[int]]) -> int:
        n = len(colors)
        g = [[] for _ in range(n)]
        for x, y in edges:
            if x == y:  
                return -1
            g[x].append(y)

        memo = [None] * n
        def dfs(x: int) -> Dict[str, int]:
            if memo[x] is not None:  # x 計算中或者計算過
                return memo[x]  # 如果是 0，表示有環
            memo[x] = 0  # 用 0 表示計算中
            res = defaultdict(int)
            for y in g[x]:
                cy = dfs(y)
                if not cy: 
                    return cy
                for ch, c in cy.items():
                    res[ch] = max(res[ch], c)
            res[colors[x]] += 1
            memo[x] = res  # 記憶化 同時代表x也搜索完畢
            return res

        ans = 0
        for x, c in enumerate(colors):
            res = dfs(x)
            if not res:  # 有環
                return -1
            ans = max(ans, res[c])
        return ans


        '''
        topological sort + DP
        n = len(colors)
        g = [[] for _ in range(n)]
        indegree = [0] * n

        for u, v in edges:
            g[u].append(v)
            indegree[v] += 1
        colors = [ord(ch) - ord('a') for ch in colors]
        dp = [[0] * 26 for _ in range(n)]  # dp[i][c] = max count of color c at node i
        q = deque()

        for i in range(n):
            if indegree[i] == 0:
                q.append(i)
                dp[i][colors[i]] = 1
        visited = 0
        ans = 0
        while q:
            u = q.popleft()
            visited += 1
            for v in g[u]:
                for c in range(26):
                    dp[v][c] = max(dp[v][c], dp[u][c] + (1 if colors[v] == c else 0))
                indegree[v] -= 1
                if indegree[v] == 0:
                    q.append(v)
            ans = max(ans, max(dp[u]))
        return ans if visited == n else -1
        '''
