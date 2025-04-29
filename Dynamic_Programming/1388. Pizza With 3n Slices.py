# TC:O(n*k) SC:O(k)
class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        '''
        任意選一個 選了以後左右兩塊也不能選 問說可以獲得最大值是多少?
        重點就在於說要如何快速判斷現在有哪些可選 哪些是他的左右兩邊
        確實有點像house robber 選or不選 可以轉化成選N個 每一個互相不在旁邊
        那就可以轉化為兩種狀況 一種是最後一個必定不選 這樣我前一個就是選or不選皆可 一個是最後可選 第一個必定不選
        '''
        n = len(slices)
        k = n // 3
        def Slices(st:int, end:int) -> int:
            # 空間優化
            no_take = [0] * (k + 1)
            take = [0] * (k + 1)
            no_take[0] = 0
            take[1] = slices[st]
            for i in range(st + 1, end + 1):
                tmp_no_take = no_take.copy()
                for j in range(1, min(i - st + 2, k + 1)): # 這次可以選到數量的最大值
                    no_take[j], take[j] = max(take[j], no_take[j]), tmp_no_take[j-1] + slices[i]
            return max(take[k], no_take[k])

            '''
            遞推
            no_take = [[0] * (k + 1) for _ in range(n)]
            take = [[0] * (k + 1) for _ in range(n)]
            no_take[st][0] = 0
            take[st][1] = slices[st]
            for i in range(st + 1, end + 1):
                for j in range(1, min(i - st + 2, k + 1)): # 這次可以選到數量的最大值
                    no_take[i][j] = max(take[i-1][j], no_take[i-1][j])
                    take[i][j] = no_take[i-1][j-1] + slices[i]
            return max(take[end][k], no_take[end][k])
            '''
            '''
            遞歸
            @cache
            def dfs(i:int, j:int) -> int:
                if i < st:
                    return 0 if j == 0 else -inf # 一定要收集到k個
                if j < 0:
                    return -inf
                ans = max(dfs(i - 2, j - 1) + slices[i], dfs(i - 1, j))
                return ans
            return dfs(end, k)
            '''
        return max(Slices(0, n-2), Slices(1, n-1))
