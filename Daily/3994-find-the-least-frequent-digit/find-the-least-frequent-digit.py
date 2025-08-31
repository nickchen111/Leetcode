class Solution:
    def getLeastFrequentDigit(self, n: int) -> int:
        cnt = Counter(str(n))
        ans = 0
        f = inf
        for x, freq in cnt.items():
            if freq < f:
                f = freq
                ans = int(x)
            elif freq == f:
                ans = min(ans, int(x))
        return ans