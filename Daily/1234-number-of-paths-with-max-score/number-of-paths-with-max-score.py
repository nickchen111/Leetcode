class Solution:
    def pathsWithMaxScore(self, board: List[str]) -> List[int]:
        MOD = 1_000_000_007
        n = len(board[0])
        max_sum = [0] + [-inf] * n
        ways = [1] + [0] * n

        for row in board:
            # 计算 max_sum[i+1][j+1] 时，pre_s 表示 max_sum[i][j]，pre_w 表示 ways[i][j]
            pre_s, pre_w = max_sum[0], ways[0]
            max_sum[0], ways[0] = -inf, 0
            for j, ch in enumerate(row):
                if ch == 'X':
                    pre_s, pre_w = max_sum[j + 1], ways[j + 1]
                    max_sum[j + 1], ways[j + 1] = -inf, 0
                    continue
                tmp_s, tmp_w = max_sum[j + 1], ways[j + 1]
                # 左上、正上、正左
                s = max(pre_s, max_sum[j + 1], max_sum[j])
                # 如果路径和相同，则累加方案数（加法原理）
                w = 0
                if pre_s == s:
                    w += pre_w
                if max_sum[j + 1] == s:
                    w += ways[j + 1]
                if max_sum[j] == s:
                    w += ways[j]
                ways[j + 1] = w % MOD
                max_sum[j + 1] = s
                if ch.isdigit():
                    max_sum[j + 1] += int(ch)  # 加上当前格子的值
                pre_s, pre_w = tmp_s, tmp_w

        return [max_sum[n], ways[n]] if max_sum[n] != -inf else [0, 0]
