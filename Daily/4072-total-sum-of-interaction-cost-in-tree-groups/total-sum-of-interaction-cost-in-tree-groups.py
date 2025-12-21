from typing import List
from collections import Counter

class Solution:
    def interactionCosts(self, n: int, edges: List[List[int]], group: List[int]) -> int:
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)
        
        total_group_cnt = Counter(group)
        max_group = 21
        
        sub_info = [[[0, 0] for _ in range(max_group)] for _ in range(n)]
        
        def dfs1(u, p):
            gu = group[u]
            sub_info[u][gu][0] = 1
            
            for v in g[u]:
                if v == p: continue
                dfs1(v, u)
                for gr in range(max_group):
                    cnt_v, dist_v = sub_info[v][gr]
                    sub_info[u][gr][0] += cnt_v
                    sub_info[u][gr][1] += (dist_v + cnt_v)

        dfs1(0, -1)
        
        ans = 0
        def dfs2(u, p, current_dist_sums):
            nonlocal ans
            ans += current_dist_sums[group[u]]
            
            for v in g[u]:
                if v == p: continue
                
                nxt_dist_sums = [0] * max_group
                for gr in range(max_group):
                    cnt_in_v = sub_info[v][gr][0]
                    cnt_out_v = total_group_cnt[gr] - cnt_in_v
                    # 換根公式：到 v 子樹內的點距離 -1，到外部的點距離 +1
                    nxt_dist_sums[gr] = current_dist_sums[gr] - cnt_in_v + cnt_out_v
                
                dfs2(v, u, nxt_dist_sums)

        initial_sums = [sub_info[0][gr][1] for gr in range(max_group)]
        dfs2(0, -1, initial_sums)
        return ans // 2