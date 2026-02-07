class Solution:
    def minimumDeletions(self, s: str) -> int:
        dp = 0        # 最小刪除次數
        b_cnt = 0     # 目前保留的 b 數量

        for c in s:
            if c == 'b':
                b_cnt += 1
            else:  # c == 'a'
                # 刪掉這個 a (dp + 1)
                # 或刪掉前面所有 b (b_cnt)
                dp = min(dp + 1, b_cnt)

        return dp
