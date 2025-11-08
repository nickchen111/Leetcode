class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
        g = [[] for _ in range(c + 1)]
        for x, y in connections:
            g[x].append(y)
            g[y].append(x)
        heaps = []
        belongs = [-1] * (c + 1)
        def dfs(x:int) -> None:
            belongs[x] = len(heaps)
            h.append(x)
            for y in g[x]:
                if belongs[y] < 0:
                    dfs(y)
        for i in range(1, c + 1):
            if belongs[i] >= 0:
                continue
            h = []
            dfs(i)
            heapify(h)
            heaps.append(h)
        offline = [False] * (c + 1)
        ans = []
        for op, x in queries:
            if op == 2:
                offline[x] = True
                continue
            if not offline[x]:
                ans.append(x)
                continue
            h = heaps[belongs[x]]
            while h and offline[h[0]]:
                heappop(h)
            ans.append(h[0] if h else -1)
        return ans