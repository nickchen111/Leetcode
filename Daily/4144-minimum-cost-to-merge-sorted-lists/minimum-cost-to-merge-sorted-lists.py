class Solution:
    def minMergeCost(self, lists: List[List[int]]) -> int:
        '''
        首先要將len做預處理 才可以快速判斷集合長度 不然每次一個集合都要去計算那就是 2^n * n 再乘上3^n會超時
        再來是中位數求法 可以用merge的概念先去判斷出找第k小元素的位置 
        最後只需要用dp去求出最小價值即可
        '''

        n = len(lists)
        u = 1 << n
        sum_len = [0] * u
        for i, len_a in enumerate(map(len, lists)):
            high_bit = 1 << i
            for s in range(high_bit):
                sum_len[high_bit | s] = sum_len[s] + len_a
       
        all_elements = sorted({x for a in lists for x in a})
        median = [0] * u
        for mask in range(1, u):
            k = (sum_len[mask] + 1) // 2
            def check(x: int) -> bool:
                cnt = 0
                for i, a in enumerate(lists):
                    if mask >> i & 1 == 0:
                        continue
                    cnt += bisect_right(a, x)
                    if cnt >= k:
                        return True
                return False
            i = bisect_left(all_elements, True, key=check)
            median[mask] = all_elements[i]
        f = [inf] * u
        for i in range(u):
            if i & (i - 1) == 0: # 代表只有一個不需要合併cost
                f[i] = 0
                continue
            j = i & (i - 1)
            while j > (i ^ j): # i ^ j = k 因為AB, E 與 E, AB會是一樣結果
                k = i ^ j
                f[i] = min(f[i], f[j] + f[k] + sum_len[j] + sum_len[k] + abs(median[j] - median[k]))
                j = (j - 1) & i
        return f[-1]



