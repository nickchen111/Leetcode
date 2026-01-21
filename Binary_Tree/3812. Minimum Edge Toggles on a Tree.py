# TC:O(nlogn) SC:O(n)
class Solution:
    def minimumFlips(self, n: int, edges: List[List[int]], start: str, target: str) -> List[int]:
        '''
        如果不一樣的點是odd 那就不可能
        偶數個要怎麼換才能達到次數最少
        '''
        g = [[] * n for _ in range(n)]
        for idx, (x, y) in enumerate(edges):
            g[x].append((y, idx))
            g[y].append((x, idx))
        ans = []
        def dfs(u:int, p:int) -> bool:
            cur = start[u] != target[u]
            for v, idx in g[u]:
                if v == p:
                    continue
                if dfs(v, u): # 代表需要翻轉
                    ans.append(idx)
                    cur = not cur
            return cur
        if dfs(0, -1):
            return [-1]
        ans.sort()
        return ans
                    
        
