# Heap: TC:O(clogc + n + qlogc) SC:O(n + c) UF: TC:O((c + q)logc) SC:O(n + c)
class Solution:
    def processQueries(self, c: int, connections: List[List[int]], queries: List[List[int]]) -> List[int]:
        # 懶刪除堆
        g = [[] for _ in range(c + 1)]
        for u, v in connections:
            g[u].append(v)
            g[v].append(u)
        heaps = []
        belongs = [-1] * (c + 1)
        def dfs(u:int) -> None:
            belongs[u] = len(heaps)
            h.append(u)
            for y in g[u]:
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

        '''
        UF + set + SortedList寫法
        fa = list(range(c + 1))
        def find(x: int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]
        def merge(u: int, v: int) -> None:
            ru, rv = find(u), find(v)
            if ru != rv:
                if ru < rv:
                    fa[rv] = ru
                else:
                    fa[ru] = rv
        for u, v in connections:
            merge(u, v)
        mp = defaultdict(SortedList)
        for i in range(1, c + 1):
            root = find(i)
            if i != root:
                mp[root].add(i)

        ans = []
        removed = set()
        for qtype, node in queries:
            if qtype == 1:
                if node not in removed:
                    ans.append(node)
                else:
                    root = find(node)
                    if node == root:
                        if mp[root]:
                            ans.append(mp[root][0])
                        else:
                            ans.append(-1)
                    else:
                        if root in removed:
                            if mp[root]:
                                ans.append(mp[root][0])
                            else:
                                ans.append(-1)
                        else:
                            ans.append(root)
            else:
                removed.add(node)
                root = find(node)
                if node in mp[root]:
                    mp[root].remove(node)
        return ans
        '''