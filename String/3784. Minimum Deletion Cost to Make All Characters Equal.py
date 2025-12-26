# TC:O(n + M) M = 26 SC:O(M)
class Solution:
    def minCost(self, s: str, cost: List[int]) -> int:
        '''
        枚舉26種看哪個cost總和最少
        '''
        tot = sum(cost)
        mp = defaultdict(int)
        for i, c in enumerate(s):
            mp[c] += cost[i]
        return min(tot - v for v in mp.values())
