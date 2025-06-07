# TC:O(n * (2^m * 2^m + m)) m = 10 SC:O(n + 2^m)
class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        '''
        n = 500 dfs解決 走到某個root 去看 0 - 9 這些是要取用哪些點的數值 但是某些點可能會佔用 3 4 
        這是否可以用mask表示
        '''
        n = len(vals) 
        maxScores = [0] * n
        g = [[] for _ in range(n)]
        for i, p in enumerate(par):
            if p != -1:
                g[p].append(i)
        MOD = 10 ** 9 + 7
        def dfs(u:int) -> List[int]:
            ans = [0] * (1 << 10)
            # 找出目前有哪些元素
            ele = 0
            val = vals[u]
            while val:
                if (ele >> (val % 10)) & 1: # 如果有相同元素 那麼根節點不選
                    ele = 0
                    break
                else:
                    ele |= (1 << (val % 10))
                val //= 10
            if ele:
                ans[ele] = vals[u]
            for v in g[u]: # 根據後面的子節點判斷目前數字扣掉前面那些的可以拼湊出的最大值是多少
                nxt = dfs(v)
                # 將之前元素的我當前有的元素扣掉 bit來說... ~
                new_ans = ans[:]
                for mask1 in range(1 << 10):
                    if ans[mask1] == 0 and mask1 != 0: continue
                    for mask2 in range(1 << 10):
                        if nxt[mask2] == 0 and mask2 != 0: continue
                        if (mask1 & mask2) == 0:
                            new_mask = mask1 | mask2
                            new_ans[new_mask] = max(new_ans[new_mask], ans[mask1] + nxt[mask2])
                ans = new_ans
            maxScores[u] = max(ans)
            return ans
        dfs(0)
        return sum(x for x in maxScores) % MOD
        
