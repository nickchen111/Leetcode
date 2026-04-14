class Solution:
    def minimumTotalDistance(self, robot: List[int], factory: List[List[int]]) -> int:
        '''
        這題就是交換論證法 證明一定找左邊 or 右邊最近的工廠修理
        '''
        robot.sort()
        factory.sort()
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0:
                return 0
            if j < 0:
                return inf
            pos, limit = factory[j]
            ans = dfs(i, j - 1) # 不選
            tot = 0
            while limit > 0 and i >= 0:
                tot += abs(pos - robot[i])
                ans = min(ans, dfs(i - 1, j - 1) + tot)
                i -= 1
                limit -= 1
            return ans
        return dfs(len(robot) - 1, len(factory) - 1)