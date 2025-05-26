# TC:O(n * Budget ^ 2) SC:O(Budget *n) list寫法
max = lambda a, b: b if b > a else a
class Solution:
    def maxProfit(self, n, present, future, hierarchy, budget):
        '''
        從特殊到一般不難想到數組的寫法需要三個參數 目前走到的元素 剩餘的預算 是否可以打折 但轉換成樹上問題就困難許多
        這題最難的就是如何分配預算給當前父節點的所有兒子
        '''
        g = [[] for _ in range(n)]
        for u, v in hierarchy:
            g[u - 1].append(v - 1)

        
        def dfs(u:int) -> List[List[int]]:
            sub_f = [[0, 0] for _ in range(budget + 1)] # 目前這個節點(might be a set) 有至多budget的空間並且能or不能使用discount 可以得到的最多收益是多少?
            for y in g[u]:
                fy = dfs(y)
                for j in range(budget, -1, -1):
                    for jy in range(j + 1): # 目前這個子節點頂多能分配的數量
                        for k in range(2):
                            sub_f[j][k] = max(sub_f[j][k], sub_f[j - jy][k] + fy[jy][k])
            f = [[0, 0] for _ in range(budget + 1)]
            for j in range(budget, -1, -1):
                for k in range(2):
                    c = present[u] // (k + 1)
                    if j >= c: # 代表目前這點可選 也可不選
                        f[j][k] = max(sub_f[j][0], sub_f[j - c][1] + future[u] - c)
                    else:
                        f[j][k] = sub_f[j][0] # 只能不選
            return f
        return dfs(0)[budget][0]
# 字典寫法 
# max = lambda a, b: b if b > a else a
fmax = lambda a, b: b if b > a else a
class Solution:
    def maxProfit(self, n, present, future, hierarchy, budget):
        '''
        從特殊到一般不難想到數組的寫法需要三個參數 目前走到的元素 剩餘的預算 是否可以打折 但轉換成樹上問題就困難許多
        這題最難的就是如何分配預算給當前父節點的所有兒子
        '''
        g = [[] for _ in range(n)]
        for u, v in hierarchy:
            g[u - 1].append(v - 1)

        
        def dfs(u:int) -> List[Dict[int, int]]:
            sub_f = [defaultdict(int), defaultdict(int)] # 目前這個節點(might be a set) 有至多budget的空間並且能or不能使用discount 可以得到的最多收益是多少?
            sub_f[0][0] = sub_f[1][0] = 0 # 在選or不選 容量0 時 所得到的最大收益都是0
            for y in g[u]:
                fy = dfs(y)
                for k, fyk in enumerate(fy):
                    nf = defaultdict(int)
                    for j, v in sub_f[k].items(): # 之前有哪些 budget 搭配 收益
                        for jy, vy in fyk.items():
                            if j + jy <= budget:
                                nf[j + jy] = fmax(nf[j + jy], v + vy)
                    sub_f[k] = nf
                        
            f = [None] * 2
            for k in range(2): # 目前這個節點選or不選
                res = sub_f[0].copy() # 不選
                c = present[u] // (k + 1)
                if budget >= c: # 代表目前這點可選 也可不選
                    earn = future[u] - c
                    for j, v in sub_f[1].items():
                        j += c
                        if j <= budget:
                            res[j] = fmax(res[j], v + earn)
                f[k] = res
                            
                #     f[j][k] = max(sub_f[j][0], sub_f[j - c][1] + future[u] - c)
                # else:
                    # f[j][k] = sub_f[j][0] # 只能不選
            return f
        return max(dfs(0)[0].values())
                        
