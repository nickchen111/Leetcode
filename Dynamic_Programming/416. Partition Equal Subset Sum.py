# TC:O(n * m) m = target / word_size SC:O(m)
class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        total = sum(nums)
        if total % 2: return False
        target = total // 2
        # bit 優化 大概是O(n * m) m 為target / word_size
        dp = 1 << 0
        mask = (1 << (target + 1)) - 1  # 產生一個遮罩，低 (target+1) 位皆為 1
        for num in nums:
            if num <= target: #也可不加這段 
                dp |= dp << num 
                dp &= mask  # 只保留 0 到 target 的位元 可不加這段 但會有小小優化
        return (dp & (1 << target)) != 0

        '''
        # 集合寫法 TC 大概是 O(n * M) M為集合中的元素 最多就是 target-1個
        dp = set()
        dp.add(0)
        for x in nums:
            new_dp = {x}
            for y in dp:
                if x + y == target:
                    return True
                if x + y < target:
                    new_dp.add(x + y)
            dp.update(new_dp)
        return False
        '''
        '''
        #空間優化
        f = [False] * (target + 1)
        f[0] = True
        for i in range(n): # 物品
            for j in range(target, nums[i]-1, -1):
                if f[j - nums[i]]:
                    f[j] = True
            if f[target]:
                return True
        return False
        '''
        '''
        遞歸
        f = [[False] * (target + 1) for _ in range(n + 1)]
        f[0][0] = True
        for i in range(n): # 物品
            f[i+1] = f[i].copy()
            for j in range(nums[i], target + 1):
                if f[i][j - nums[i]]:
                    f[i+1][j] = True
        return f[n][target]
        '''
        '''
        遞歸
        @cache
        def dfs(i:int, sum:int):
            if i < 0:
                return True if sum == target else False
            if sum > target:
                return False
            return dfs(i-1, sum) or dfs(i-1, sum + nums[i])
        return dfs(n-1, 0)
        '''
