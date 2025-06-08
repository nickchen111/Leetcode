# TC:O(n * (3^m + U)) m = 10 U = 數值十進制長度 SC:O(n + n * 2^m)
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
            # ans = [0] * (1 << 10)
            ans = defaultdict(int)
            ans[0] = 0
            # 找出目前有哪些元素
            ele = 0
            val = vals[u]
            while val:
                val,d = divmod(val, 10)
                if (ele >> d) & 1: # 如果有相同元素 那麼根節點不選
                    break
                else:
                    ele |= (1 << d)
            else:
                ans[ele] = vals[u]
            for v in g[u]: # 根據後面的子節點判斷目前數字扣掉前面那些的可以拼湊出的最大值是多少
                nxt = dfs(v)
                # new_ans = ans[:]
                new_ans = ans.copy()
                # for mask1 in range(1 << 10):
                for mask1, s in ans.items():
                    # if ans[mask1] == 0 and mask1 != 0: continue
                    # for mask2 in range(1 << 10):
                    for mask2, s2 in nxt.items():
                        # if nxt[mask2] == 0 and mask2 != 0: continue
                        if (mask1 & mask2) == 0:
                            new_mask = mask1 | mask2
                            new_ans[new_mask] = max(new_ans[new_mask], ans[mask1] + nxt[mask2])
                ans = new_ans.copy()
            maxScores[u] = max(ans.values())
            return ans
        dfs(0)
        return sum(x for x in maxScores) % MOD
