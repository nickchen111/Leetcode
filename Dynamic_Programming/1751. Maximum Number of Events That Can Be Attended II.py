# TC:O(n * k + n * lgn) SC:O(n * k)
class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        '''
        這題在基礎上多加了只能選k天限制 但是兩個變數時間複雜度來說還是1e6範圍內
        '''
        events.sort(key=lambda x:x[1])
        n = len(events)
        f = [[0] * (k+1) for _ in range(n+1)]
        for i in range(n):
            start, end, val = events[i]
            t = bisect_left(events, start, hi=i, key=lambda e: e[1])
            for j in range(k): # 因為是至多k個 所以 j > i + 1 也要列入計算 也就是答案回傳f[n][k]時要考慮少於k狀態
                f[i+1][j+1] = max(f[i][j+1], f[t][j] + val)
        return f[n][k]
