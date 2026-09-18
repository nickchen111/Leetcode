class Solution:
    def maxNumOfSubstrings(self, s: str) -> list[str]:

        n = len(s)

        pre = [n] * 26
        suf = [-1] * 26

        for i, ch in enumerate(s):
            x = ord(ch) - ord('a')

            if pre[x] == n:
                pre[x] = i

            suf[x] = i

        # 找合法 intervals
        intervals = []

        for x in range(26):

            if suf[x] == -1:
                continue

            l = pre[x]
            r = suf[x]

            j = l
            valid = True

            while j <= r:

                c = ord(s[j]) - ord('a')

                if pre[c] < l:
                    valid = False
                    break

                r = max(r, suf[c])
                j += 1

            if valid:
                intervals.append((l, r))

        intervals.sort(key=lambda x: x[1])

        # dp[i]:
        # 考慮 s[:i]
        #
        # dp_cnt[i] = 最大 substring 數量
        # dp_len[i] = 在最大數量下的最小總長度

        dp_cnt = [0] * (n + 1)
        dp_len = [0] * (n + 1)

        parent = [-1] * (n + 1)
        choice = [None] * (n + 1)

        k = 0

        for i in range(1, n + 1):

            # Case 1: 不選結尾在 i-1 的 substring
            dp_cnt[i] = dp_cnt[i - 1]
            dp_len[i] = dp_len[i - 1]

            parent[i] = i - 1
            choice[i] = None

            # Case 2: 選擇 [l, r]
            while k < len(intervals) and intervals[k][1] + 1 == i:

                l, r = intervals[k]

                new_cnt = dp_cnt[l] + 1
                new_len = dp_len[l] + (r - l + 1)

                if (
                    new_cnt > dp_cnt[i]
                    or (
                        new_cnt == dp_cnt[i]
                        and new_len < dp_len[i]
                    )
                ):
                    dp_cnt[i] = new_cnt
                    dp_len[i] = new_len

                    parent[i] = l
                    choice[i] = (l, r)

                k += 1

        # traceback
        ans = []

        i = n

        while i > 0:

            if choice[i] is not None:

                l, r = choice[i]

                ans.append(s[l:r + 1])

                i = l

            else:

                i = parent[i]

        return ans