# TC:O(3 * 3 *  n * ((n-1)) / 2) SC:O(n * 3)
class Solution:
    def countWinningSequences(self, s: str) -> int:
        """
        已知 Alice 召喚的順序 (s)，Bob 不能連續召喚相同神獸。
        神獸間的克制關係：
            F > E, W > F, E > W
        """
        mapping = {'W': 0, 'E': 1, 'F': 2}
        n = len(s)
        MOD = 10 ** 9 + 7
        # 空間優化
        # dp: 用字典保存狀態：key=(score, last)，value=計數
        dp = {}
        for j in range(3):
            outcome = (j - mapping[s[0]] + 3) % 3
            if outcome == 1:
                score = 1
            elif outcome == 0:
                score = 0
            else:
                score = -1
            dp[(score, j)] = 1

        for i in range(1, n):
            new_dp = {}
            for (score, last), count in dp.items():
                for j in range(3):
                    if j == last:
                        continue
                    outcome = (j - mapping[s[i]] + 3) % 3
                    if outcome == 1:
                        new_score = score + 1
                    elif outcome == 0:
                        new_score = score
                    else:
                        new_score = score - 1
                    key = (new_score, j)
                    new_dp[key] = (new_dp.get(key, 0) + count) % MOD
            dp = new_dp
        return sum(count for (score, _), count in dp.items() if score > 0) % MOD

        '''
        遞推
        OFFSET = n
        f = [[[0] * 3 for _ in range(n + 1 + OFFSET)] for _ in range(n)]
        for j in range(3):
            if (j - mapping[s[0]] + 3) % 3 == 1:
                f[0][1 + OFFSET][j] = 1
            elif (j - mapping[s[0]] + 3) % 3 == 0:
                f[0][0 + OFFSET][j] = 1
            else:
                f[0][OFFSET - 1][j] = 1
        for i in range(1, n):
            for j in range(-i, i + 1):
                for k in range(3):
                    for t in range(3):
                        if k != t:
                            if (k - mapping[s[i]] + 3) % 3 == 1:
                                f[i][j + OFFSET + 1][k] = (f[i][j + OFFSET + 1][k] + f[i-1][j + OFFSET][t]) % MOD
                            elif (k - mapping[s[i]] + 3) % 3 == 0:
                                f[i][j + OFFSET][k] = (f[i][j + OFFSET][k] + f[i-1][j + OFFSET][t]) % MOD
                            else:
                                f[i][j + OFFSET - 1][k] = (f[i][j + OFFSET - 1][k] + f[i-1][j + OFFSET][t]) % MOD
        return sum(f[n-1][j][k] for j in range(OFFSET+1, n + OFFSET + 1) for k in range(3)) % MOD
        '''
        '''
        遞歸
        TC: n * n * 4 * 3
        @cache
        def dfs(i: int, tot: int, prev: int) -> int:
            # 當剩餘回合再輸也保證獲勝：當 tot - (n-i) > 0 時
            if tot - (n - i) > 0:
                # 如果還沒開始選擇(無前導限制)，第一回合有 3 種選擇，之後每回合只能從 2 種中選
                return (3 * pow(2, n - i - 1, MOD)) % MOD if prev == -1 else pow(2, n - i, MOD)
            # 當剩餘回合即使全贏，也無法將 tot 提升到 >0，就剪枝返回 0
            if tot + (n - i) < 0:
                return 0
            if i == n:
                return 1 if tot > 0 else 0
            
            cur_alice = mapping[s[i]]
            ans = 0
            for j in range(3):
                if j == prev:
                    continue
                # 利用模運算來判斷勝負：diff = (j - cur_alice + 3) % 3
                diff = (j - cur_alice + 3) % 3
                if diff == 1:  # Bob 獲勝
                    ans = (ans + dfs(i + 1, tot + 1, j)) % MOD
                elif diff == 0:  # 平局
                    ans = (ans + dfs(i + 1, tot, j)) % MOD
                else:  # diff == 2, Bob 失敗
                    ans = (ans + dfs(i + 1, tot - 1, j)) % MOD
            return ans
        return dfs(0, 0, -1) % MOD
        '''
