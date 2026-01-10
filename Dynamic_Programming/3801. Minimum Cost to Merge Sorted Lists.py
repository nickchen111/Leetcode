# TC:O(3^n + 2 ^ n) SC:O(2^n)
class Solution:
    def minMergeCost(self, lists: List[List[int]]) -> int:
        n = len(lists)
        u = 1 << n
        sum_len = [0] * u
        median = [0] * u
        for i, len_a in enumerate(map(len, lists)):
            high_bit = 1 << i
            for j in range(high_bit):
                sum_len[high_bit | j] = sum_len[j] + len_a
        all_elements = sorted({x for a in lists for x in a})
        for mask in range(1, u):
            k = (sum_len[mask] + 1) // 2
            def check(x:int) -> int:
                cnt = 0
                for i, a in enumerate(lists):
                    if mask >> i & 1 == 0:
                        continue
                    cnt += bisect_right(a, x)
                    if cnt >= k:
                        return True
                return False
            i = bisect_left(all_elements, True, key = check)
            median[mask] = all_elements[i]
        f = [inf] * u
        for i in range(u): # 3^12 ~= 1e5 如果沒預處理會爆掉 * 500
            if i & (i - 1) == 0:
                f[i] = 0
                continue
            j = i & (i - 1) # 把一個拿掉
            while j > (i ^ j):
                k = i ^ j
                f[i] = min(f[i], f[j] + f[k] + sum_len[j] + sum_len[k] + abs(median[j] - median[k])) # 這裏發現需要預處理len, median
                j = (j - 1) & i
        return f[-1]
