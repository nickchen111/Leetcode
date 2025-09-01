class Solution:
    def getLeastFrequentDigit(self, n: int) -> int:
        cnt = Counter(str(n))
        min_ch = min((c, ch) for ch, c in cnt.items())[1] # 這樣就可以順便比較頻率相同的狀況選最小的ch 不用額外寫if else
        return int(min_ch)