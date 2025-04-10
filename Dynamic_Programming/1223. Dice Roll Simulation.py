# T:O(n * 6 * 6 * k) SC:O(6 * k)
class Solution:
    def dieSimulator(self, n: int, rollMax: List[int]) -> int:
        '''
        每個數字出現的連續次數不能超過各自的limit 那會有多少種可能性
        n = 5000 總共會丟這麼多次, rollMax = 15,上一個是誰 總共出現了幾次
        '''
        MOD = 10 ** 9 + 7
        r_max = max(rollMax)
        f = [[0] * (r_max + 1) for _ in range(6)]
        for i in range(6):
            f[i][1] = 1
        for i in range(1, n):
            new_f = [[0] * (r_max + 1) for _ in range(6)]
            for pre in range(6):
                for cur in range(6):
                    if cur != pre:
                        # 當更換骰子面時，連續次數重設為 1
                        new_f[cur][1] = (new_f[cur][1] + sum(f[pre][cnt] for cnt in range(1, min(rollMax[pre], i + 1) + 1))) % MOD
                    else:
                        # 當保持骰子面不變時，連續次數增加 1，但必須不超過該面限制
                        for cnt in range(1, min(rollMax[pre], i + 1)):
                            new_f[cur][cnt + 1] = (new_f[cur][cnt + 1] + f[cur][cnt]) % MOD
            f = new_f
        return sum(sum(row) for row in f) % MOD

        '''
        @cache
        def dfs(i:int, pre:int, cnt:int) ->int:
            if i == n:
                return 1
            ans = 0
            for j in range(1, 7):
                if j != pre:
                    ans = (ans + dfs(i+1, j, 1)) % MOD
                elif j == pre and cnt + 1 <= rollMax[j-1]:
                    ans = (ans + dfs(i+1, j, cnt + 1)) % MOD
            return ans
        return dfs(0, -1, 0)
        '''
