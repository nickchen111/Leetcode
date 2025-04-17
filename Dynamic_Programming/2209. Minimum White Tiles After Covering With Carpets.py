# TC:O(n * n) SC:O(n)
class Solution:
    def minimumWhiteTiles(self, floor: str, numCarpets: int, carpetLen: int) -> int:
        '''
        給你一串binary string floor，你有n個毯子 每個 len長度 可重疊的去覆蓋string 
        問說最少會剩下多少個白色
        len = floor = n = 1000
        我會想到會去跑一個dfs看說 目前要從哪開始 還剩下多少個crapet 他蓋完以後後面就肯定從 沒蓋到的地方繼續
        萬一蓋到超過floor size 就返回0, 那如果毯子都用完了 還沒蓋完所有的位置 就預處理走到某個floor pos之前有多少個白色 return 該數量
        1. 預處理 floor pos之前會有多少個白色 我會用vector陣列做這件事
        2. 去跑dfs 從 n = floor.size() - 1 開始, numCarpets數量
        3. 遞歸邊界會是 i < 0 or num == 0
        '''
        n = len(floor)
        floor = list(map(int, floor))
        # 空間優化
        f = list(accumulate(floor))
        for i in range(1, numCarpets + 1):
            nf = [0] * n
            for j in range(i * carpetLen, n):
                nf[j] = min(nf[j-1] + floor[j], f[j - carpetLen]) # 選or不選
            f = nf
        return f[-1]
        '''
        遞推
        f = [[0] *  n for i in range(numCarpets + 1)]
        f[0] = list(accumulate(floor))
        for i in range(1, numCarpets + 1):
            for j in range(i * carpetLen, n):
                f[i][j] = min(f[i][j-1] + floor[j], f[i-1][j - carpetLen]) # 選or不選
        return f[-1][-1]
        '''

        '''
        遞歸
        pre = [0] * n
        for i in range(n):
            pre[i] = pre[i-1] + floor[i]
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0:
                return 0
            if j == 0:
                return pre[i]
            if j * carpetLen > i:
                return 0
            cand1 = dfs(i-1, j) + floor[i]
            cand2 = dfs(i - carpetLen, j - 1)
            return cand1 if cand1 < cand2 else cand2
            # return min(dfs(i-1, j) + (1 if floor[i] == '1' else 0), dfs(i - carpetLen, j - 1))
        return dfs(n-1, numCarpets)
        '''
