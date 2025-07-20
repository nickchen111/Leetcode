# TC:O(n) SC:O(n) n為y軸長度
MOD = 10 ** 9 + 7
class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        mp = defaultdict(int)
        for px, py in points:
            mp[py] += 1
        pairs_by_y = {}
        for py, cnt in mp.items():
            if cnt >= 2:
                pairs_by_y[py] = comb(cnt, 2)
        ans = 0
        total = sum(pairs_by_y.values())
        for py, pair_cnt in pairs_by_y.items():
            total -= pair_cnt
            ans += total * pair_cnt
        return ans % MOD
