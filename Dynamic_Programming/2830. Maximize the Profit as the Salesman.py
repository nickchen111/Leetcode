# TC:O(n + m) SC:O(n + m)
class Solution:
    def maximizeTheProfit(self, n: int, offers: List[List[int]]) -> int:
        groups = [[] for _ in range(n)]
        for st, end, gold in offers:
            groups[end].append((st,gold))
        f = [0] * (n + 1)
        for end, g in enumerate(groups):
            f[end+1] = f[end] #不選
            for start, gold in g:
                if f[start] + gold > f[end+1]:
                    f[end+1] = f[start] + gold
        return f[n]

