# TC:O(n + M) M 為字符串集合大小 SC:O(M)
class Solution:
    def score(self, cards: List[str], x: str) -> int:
        def cal(cnt: Dict[str, int]) -> Tuple[int,int]:
            sum_cnt = sum(cnt.values())
            max_cnt = max(cnt.values(), default=0)
            pairs = min(sum_cnt // 2, sum_cnt - max_cnt)

            return pairs, sum_cnt - 2 * pairs
        cnt = Counter(cards)
        cnt_xx = cnt.pop(x + x, 0)
        cnt1 = {b : c for (a, b), c in cnt.items() if a == x}
        cnt2 = {a : c for (a, b), c in cnt.items() if b == x}
        pairs1, left1 = cal(cnt1)
        pairs2, left2 = cal(cnt2)
        ans = pairs1 + pairs2

        if cnt_xx > 0:
            mn = min(cnt_xx, left1 + left2)
            ans += mn
            cnt_xx -= mn
        
        if cnt_xx > 0:
            ans += min(cnt_xx // 2, pairs1 + pairs2)
        return ans


# 
class Solution:
    def get_sum_and_max(self, cnt: Dict[str, int]) -> Tuple[int, int]:
        sum_cnt = sum(cnt.values())
        max_cnt = max(cnt.values(), default=0)
        return sum_cnt, max_cnt

    def calc_score(self, s: int, mx: int, k: int) -> int:
        s += k
        mx = max(mx, k)
        return min(s // 2, s - mx)

    def score(self, cards: List[str], x: str) -> int:
        cnt = Counter(cards)
        cnt_xx = cnt.pop(x + x, 0)
        cnt1 = {b: c for (a, b), c in cnt.items() if a == x}
        cnt2 = {a: c for (a, b), c in cnt.items() if b == x}

        sum1, max1 = self.get_sum_and_max(cnt1)
        sum2, max2 = self.get_sum_and_max(cnt2)

        ans = 0
        for k in range(cnt_xx + 1):
            score1 = self.calc_score(sum1, max1, k)
            score2 = self.calc_score(sum2, max2, cnt_xx - k)
            ans = max(ans, score1 + score2)
        return ans
