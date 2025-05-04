# TC:O(n) SC:O(n)
class Solution:
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:
        cnt = defaultdict(int)
        n = len(dominoes)
        ans = 0
        for i in range(n):
            a, b = dominoes[i][0], dominoes[i][1]
            val =  a * 10 + b if a > b else b * 10 + a
            cnt[val] += 1
            ans += cnt[val] - 1
        return ans
