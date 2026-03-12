class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        '''
        must = 0可以update 1 time
        所有數字找出最小的stregth 要讓all edges included it
        求最大可以是多少
        如果無法connect all node return -1
        1. 先確定能否形成spanning tree
        2. 找出最大可以是多少? 二分找
        3. must必定要先連 然後就看缺少哪些點 找出當前邊中有連接到該點的 可以用UF確認是否同一個邊 不同的話嘗試連
        '''
        class UnionFind:
            def __init__(self, n):
                self.parent = list(range(n))
                self.components = n
            
            def find(self, x):
                if self.parent[x] != x:
                    self.parent[x] = self.find(self.parent[x])
                return self.parent[x]
            
            def union(self, x, y):
                px, py = self.find(x), self.find(y)
                if px == py:
                    return False
                if px < py:
                    px, py = py, px
                self.parent[py] = px
                self.components -= 1
                return True
            
            def connected(self):
                return self.components == 1
        must_edges = []
        min_s, max_s = inf, -inf
        uf_all = UnionFind(n)
        uf_must = UnionFind(n)
        min_must = inf
        for u, v, s, must in edges:
            if must == 1 and not uf_must.union(u, v):
                return -1
            uf_all.union(u, v)
            if must == 1:
                min_must = min(min_must, s)
            min_s = min(min_s, s)
            max_s = max(max_s, s)
        if not uf_all.connected():
            return -1
        uf_template = UnionFind(n)
        for u, v, s, must in edges:
            if must == 1:
                uf_template.union(u, v)
        def check(mid):
            if mid > min_must:
                return False
            uf = copy.deepcopy(uf_template)
            avalibleEdges = []
            cnt = 0
            for u, v, s, must in edges:
                if must == 0:
                    if s >= mid:
                        uf.union(u, v) # 不需升級
                    elif s * 2 >= mid:
                        avalibleEdges.append((u, v, s))
            for u, v, s in avalibleEdges:
                if uf.find(u) != uf.find(v):
                    if cnt < k:
                        uf.union(u, v)
                        cnt += 1
                        if uf.connected():
                            return True
            return uf.connected()
        left, right = min_s, max_s * 2 + 1
        ans = -1
        while left < right:
            mid = (left + right + 1) // 2
            if check(mid):
                left = mid
            else:
                right = mid - 1
        return left