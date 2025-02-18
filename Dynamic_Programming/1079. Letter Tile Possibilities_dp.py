# TC:O(n^2) SC:O(n)
class Solution:
    def numTilePossibilities(self, tiles: str) -> int:
        n = len(tiles)
        counter = Counter(tiles)
        # 背包概念可壓掉一個空間維度
        dp = [0] * (n+1)
        dp[0] = 1
        for _, freq in counter.items():
            for l in range(n, 0, -1):
                for k in range(1, min(l, freq) + 1): 
                    dp[l] += dp[l-k] * comb(l, k)
        return sum(dp[1:])

        '''
        二維寫法
        dp = [[0] * (n+1) for _ in range(len(counter)+1)]
        dp[0][0] = 1

        cnt = 1
        for _, freq in counter.items():
            for l in range(n+1):
                dp[cnt][l] = dp[cnt-1][l]
                for k in range(1, min(l, freq) + 1): 
                    dp[cnt][l] += dp[cnt-1][l-k] * comb(l, k)
            cnt += 1 
        return sum(dp[len(counter)][1:])
        '''
