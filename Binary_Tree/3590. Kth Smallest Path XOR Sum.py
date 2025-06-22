# TC:O(nlg^2(n) + qlgn) SC:O(n + q)
class Solution:
    def kthSmallest(self, par: List[int], vals: List[int], queries: List[List[int]]) -> List[int]:
        n = len(par)
        g = [[] for _ in range(n)]
        for i in range(1, n):
            g[par[i]].append(i)
        # offline query
        qs = [[] for _ in range(n)]
        for i, (q, k) in enumerate(queries):
            qs[q].append((k, i))
        ans = [-1] * len(queries) 
        def dfs(u:int, pa:int, xor:int) -> SortedSet():
            xor ^= vals[u]
            st = SortedSet()
            st.add(xor)
            for nxt in g[u]:
                if nxt != pa:
                    set_nxt = dfs(nxt, u, xor)
                if len(set_nxt) > len(st):
                    st, set_nxt = set_nxt, st
                for v in set_nxt:
                    st.add(v)
            nonlocal ans
            for k, i in qs[u]:
                if k - 1 < len(st):
                    ans[i] = st[k - 1]
            return st
        dfs(0, -1, 0)
        return ans
