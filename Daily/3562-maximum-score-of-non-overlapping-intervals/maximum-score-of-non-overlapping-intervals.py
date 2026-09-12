class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        '''
        選最多四個不重疊區間最大化可以得到的weight，問說這四個區間的index是哪些，如果有很多答案 選擇字典序最小的
        首先 狀態會定義成 f[n][k] 走到哪裡 選了多少個區間的最大值
        用另一個數組紀錄 例如 pos[i][j] 走到i的時候組成k個他可以有的最大值是來自於哪一組的index
        '''
        n = len(intervals)
        a = [(end, start, weight, i) for i, (start, end, weight) in enumerate(intervals)]
        a.sort(key=lambda x:x[0])
        f = [[(0, []) for _ in range(5)] for _ in range(n+1)]
        for i, (end, start, weight, idx) in enumerate(a):
            t = bisect_left(a, (start,), hi=i)
            for j in range(4):
                s2, id2 = f[t][j]
                if s2 + weight > f[i][j+1][0]:
                    f[i+1][j+1] = (s2 + weight, sorted([idx] + id2))
                elif s2 + weight == f[i][j+1][0]:
                    if sorted([idx] + id2) < f[i][j+1][1]:
                        f[i+1][j+1] = (s2 + weight, sorted([idx] + id2))
                    else: f[i+1][j+1] = f[i][j+1]
                else: f[i+1][j+1] = f[i][j+1]
                        
        return f[n][4][1]
       