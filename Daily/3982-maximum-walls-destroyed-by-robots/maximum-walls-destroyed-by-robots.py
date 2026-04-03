class Solution:
    def maxWalls(self, robots: List[int], distance: List[int], walls: List[int]) -> int:
        '''
        子彈碰到機器人會停下來 每個機器人有一發子彈 問說最多可以打碎多少面牆
        子彈最多走distance[i]距離
        設計一個算法去判斷 目前這個位置我往左打以及右打可以收集到的最多walls是多少
        1. 往左打
           1.1 上一個是往左打 
           dp[i][0] = dp[i - 1][0] + 左邊這段範圍 看可以收集多少 max(robots[i] - robots[i - 1], robot[i]  - distance[i])可以收集的walls 並且如果左邊沒有機器人那麼要跟1取最大值
           1.2 上一個往右打
               1.2.1 與上一個的區間沒有重疊
               dp[i][1] = dp[i - 1][1] + (robots[i] - distance[i]可以收集的walls)
               1.2.3 上個區間重疊
               dp[i][1] = dp[i - 1][1] + max(1, robots[i] - (robots[i - 1] + distance[i]) + 1) 規定上一個打過來也不能超過我
        2. 往右打
           dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + sum(min(robots[i + 1] - robot[i], robots[i] + distance[i]))
        問題變成要如何知道每一個部分的牆壁總和 -> prefix sum 但是值域到1e9 是否可以做idx mapping
        先將walls位置mapping成index
        每次要找目前robot可以獲取的位置的時候 就對walls mapping index的資料結構二分找出index 就可以計算有多少個牆壁了
        '''
        idx = sorted(range(len(robots)), key=lambda i: robots[i])
        walls.sort()
        # 哨兵
        walls.append(inf)
        dp = [[0] * 2 for _ in range(len(robots) + 1)]
        for i, x in enumerate(idx):
            # 1. 往左打 首先要先將這次往左打能走到的範圍取出
            left, right = max(robots[idx[i - 1]] + 1 if i - 1 >= 0 else 0, robots[x] - distance[x]), robots[x]
            # 1.1 上一個是往左打
            left_boundary = bisect_left(walls, left)
            right_boundary = bisect_right(walls, right)
            dp[i + 1][0] = max(dp[i + 1][0], dp[i][0] + right_boundary - left_boundary)
            # 1.2 上一個往右打
            left, right = max(robots[x] - distance[x], min(robots[x], robots[idx[i - 1]] + distance[idx[i - 1]] + 1 if i - 1 >= 0 else 0)), robots[x]
            # 1.2.1 與上一個的區間沒有重疊 & 上個區間重疊
            left_boundary = bisect_left(walls, left)
            right_boundary = bisect_right(walls, right)
            dp[i + 1][0] = max(dp[i + 1][0], dp[i][1] + right_boundary - left_boundary)
            # 2. 往右打
            left, right = robots[x], min(robots[x] + distance[x], robots[idx[i + 1]] - 1 if i + 1 < len(idx) else robots[x] + distance[x])
            left_boundary = bisect_left(walls, left)
            right_boundary = bisect_right(walls, right)
            dp[i + 1][1] = max(dp[i][1], dp[i][0]) + right_boundary - left_boundary
        return max(dp[-1][0], dp[-1][1])





