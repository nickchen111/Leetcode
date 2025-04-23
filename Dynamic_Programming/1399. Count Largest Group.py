# TC:O(m * k) SC:O(m * k + k) m = 數字轉字串長度, k = 總和最大值
class Solution:
    def countLargestGroup(self, n: int) -> int:
        digits = list(map(int, str(n)))
        L = len(digits)
        @cache
        def dfs(pos: int, s: int, is_limit: bool) -> Counter:
            if pos == L:
                return Counter({s: 1})
            res = Counter()
            upper = digits[pos] if is_limit else 9
            for d in range(0, upper + 1):
                res += dfs(pos + 1, s + d, is_limit and (d == upper))
            return res

        cnt = dfs(0, 0, True)
        cnt[0] -= 1
        max_size = max(cnt.values())
        return sum(1 for v in cnt.values() if v == max_size)

