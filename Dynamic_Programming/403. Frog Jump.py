# TC:O(n * U) U為每個跳到的點平均可能有的下一步啟動步數 SC:O(n * U)
class Solution:
    def canCross(self, stones: List[int]) -> bool:
        '''
        每次我的跳躍可以是k-1, k, k + 1但是一定要是正數
        從0出發，起始jump = 1
        問說能否跳到終點
        我會想到的是狀態定義為 跳到第i個石頭，我目前可以跳躍的距離
        '''
        n = len(stones)
        if stones[1] != 1: return False
        
        stone_set = set(stones)
        # 使用字典，每個石頭記錄可用來跳到下一個石頭的跳躍值集合
        dp = {stone: set() for stone in stones}
        dp[0].add(1)
        
        for stone in stones:
            # 對當前石頭的每個可能跳躍值
            for jump in dp[stone]:
                next_stone = stone + jump
                if next_stone == stones[-1]:
                    return True
                if next_stone in stone_set:
                    if jump - 1 > 0:
                        dp[next_stone].add(jump - 1)
                    dp[next_stone].add(jump)
                    dp[next_stone].add(jump + 1)
        return False

        '''
        @cache
        def dfs(pos:int, j:int) -> bool:
            if pos == stones[n-1]:
                return True
            ans = False
            # 這邊需要確認後面是否真的有這個位置
            if j - 1 > 0 and pos + j - 1 in stone_set:
                ans |= dfs(pos + j - 1, j - 1)
            if pos + j in stone_set:
                ans |= dfs(pos + j, j)
            if pos + j + 1 in stone_set:
                ans |= dfs(pos + j + 1, j + 1)
            return ans
        return dfs(1, 1)
        '''
