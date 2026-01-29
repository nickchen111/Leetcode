# Trie TC:O(n^2 + mn + m^3) SC:O(n + mn + m^2)
class TrieNode:
    __slot__ = 'id', 'son'
    def __init__(self):
        self.son = [None] * 26
        self.id = -1

class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        '''
        source 變成1000 可以n^2 看起來是為了讓你拆分substring 
        target.length = 100, str = 1000 -> 10 ** 5
        '''
        ord_a = ord('a')
        root = TrieNode()
        id = 0
        n = len(source)
        def put(s:str) -> int:
            node = root
            for c in s:
                i = ord(c) - ord_a
                if node.son[i] is None:
                    node.son[i] = TrieNode()
                node = node.son[i]
            if node.id < 0:
                nonlocal id
                node.id = id
                id += 1
            return node.id

        m = len(cost)
        dist = [[inf] * (m * 2) for _ in range(m * 2)]
        for ori, ch, c in zip(original, changed, cost):
            x = put(ori)
            y = put(ch)
            dist[x][y] = min(dist[x][y], c)
        for k in range(id):
            for i in range(id):
                if dist[i][k] == inf:
                    continue
                for j in range(id):
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        
        @cache
        def dfs(i:int) -> int:
            if i == n:
                return 0
            res = inf
            if source[i] == target[i]:
                res = dfs(i + 1)
            p, q = root, root
            for j in range(i, n):
                p = p.son[ord(source[j]) - ord_a]
                q = q.son[ord(target[j]) - ord_a]
                if p is None or q is None:
                    break
                if p.id < 0 or q.id < 0:
                    continue
                res = min(res, dfs(j + 1) + dist[p.id][q.id])
            return res
        ans = dfs(0)
        return ans if ans != inf else -1

class TrieNode:
    __slot__ = 'id', 'son'
    def __init__(self):
        self.son = [None] * 26
        self.id = -1

class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        ord_a = ord('a')
        root = TrieNode()
        id = 0
        n = len(source)
        def put(s:str) -> int:
            node = root
            for c in s:
                i = ord(c) - ord_a
                if node.son[i] is None:
                    node.son[i] = TrieNode()
                node = node.son[i]
            if node.id < 0:
                nonlocal id
                node.id = id
                id += 1
            return node.id

        m = len(cost)
        dist = [[inf] * (m * 2) for _ in range(m * 2)]
        for ori, ch, c in zip(original, changed, cost):
            x = put(ori)
            y = put(ch)
            dist[x][y] = min(dist[x][y], c)
        for k in range(id):
            for i in range(id):
                if dist[i][k] == inf:
                    continue
                for j in range(id):
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        
        f = [inf] * n + [0]
        for i in range(n - 1, -1, -1):
            if source[i] == target[i]:
                f[i] = f[i + 1]
            p, q = root, root
            for j in range(i, n):
                p = p.son[ord(source[j]) - ord_a]
                q = q.son[ord(target[j]) - ord_a]
                if p is None or q is None:
                    break
                if p.id < 0 or q.id < 0:
                    continue
                f[i] = min(f[i], f[j + 1] + dist[p.id][q.id])
        return f[0] if f[0] != inf else -1


# 根據字串長度的分法
class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        len_to_strs = defaultdict(set)
        dis = defaultdict(lambda: defaultdict(lambda: inf))
        for x, y, c in zip(original, changed, cost):
            len_to_strs[len(x)].add(x)
            len_to_strs[len(y)].add(y)
            dis[x][y] = min(dis[x][y], c)
            dis[x][x] = 0
            dis[y][y] = 0

        for strs in len_to_strs.values():
            for k in strs:
                for i in strs:
                    if dis[i][k] == inf:
                        continue
                    for j in strs:
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j])

        n = len(source)
        f = [0] + [inf] * n
        for i in range(1, n + 1):
            if source[i - 1] == target[i - 1]:
                f[i] = f[i - 1]
            for size, strs in len_to_strs.items():
                if i < size:
                    continue
                s = source[i - size: i]
                t = target[i - size: i]
                if s in strs and t in strs:
                    f[i] = min(f[i], dis[s][t] + f[i - size])
        return f[n] if f[n] < inf else -1
