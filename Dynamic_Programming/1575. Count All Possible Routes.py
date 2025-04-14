# TC:O(n * n * m) SC:O(n * m)
class Solution:
    def countRoutes(self, locations: List[int], start: int, finish: int, fuel: int) -> int:
        '''
        從 start ~ finish 問說有多說種走法並且fuel是固定的不能 < 0
        每次你走的時候 會消耗abs(location[i] - location[j])
        '''
        MOD = 10 ** 9 + 7
        n = len(locations)
        start_location = locations[start]
        finish_location = locations[finish]
        locations.sort()
         #遞歸 藉由sort優化 就可以及時打住 不用全部traverse
        @cache
        def dfs(location_id:int, j:int) -> int:
            location = locations[location_id]
            ans = 1 if location == finish_location else 0
            for k in range(location_id+1,n):
                if abs(location - locations[k]) <= j:
                    ans = (ans + dfs(k, j - abs(location - locations[k]))) % MOD
                else:
                    break
            for k in range(location_id - 1, -1, -1):
                if abs(location - locations[k]) <= j:
                    ans = (ans + dfs(k, j - abs(location - locations[k]))) % MOD
                else:
                    break
            return ans
        start_id = locations.index(start_location)
        # print(start_id)
        return dfs(start_id, fuel) % MOD
        '''
        # 遞推優化 藉由sort優化 就可以及時打住 不用全部traverse
        start_id = locations.index(start_location)
        finish_id = locations.index(finish_location)
        dp = [[0] * (fuel + 1) for _ in range(n)]
        dp[start_id][fuel] = 1
        for f in range(fuel, -1, -1):
            for i in range(n):
                for j in range(i+1, n):
                    cost = abs(locations[i] - locations[j])
                    if f >= cost:
                        dp[j][f - cost] = (dp[j][f - cost] + dp[i][f]) % MOD
                    else: break
                for j in range(i-1, -1, -1):
                    cost = abs(locations[i] - locations[j])
                    if f >= cost:
                        dp[j][f - cost] = (dp[j][f - cost] + dp[i][f]) % MOD
                    else: break
        return sum(dp[finish_id][j] for j in range(fuel+1)) % MOD
        '''
       
