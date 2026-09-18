class Solution:
    def maxNumOfSubstrings(self, s: str) -> list[str]:

        n = len(s)

        pre = [n] * 26
        suf = [-1] * 26

        # 1. first / last occurrence
        for i, ch in enumerate(s):
            x = ord(ch) - ord('a')

            if pre[x] == n:
                pre[x] = i

            suf[x] = i

        # 2. 找合法 intervals
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

                # 有 occurrence 在 l 左邊
                if pre[c] < l:
                    valid = False
                    break

                # 必須把右界延伸
                r = max(r, suf[c])

                j += 1

            if valid:
                intervals.append((l, r))

        # 3. DP
        dp = [0] * (n + 1)

        # parent[i] = 從哪裡轉移
        parent = [-1] * (n + 1)

        # choice[i] = 如果選 substring，記錄 [l, r]
        choice = [None] * (n + 1)

        # 先按照 r 排序
        intervals.sort(key=lambda x: x[1])

        k = 0

        for i in range(1, n + 1):

            # 不選任何 substring 結尾於 i-1
            dp[i] = dp[i - 1]
            parent[i] = i - 1

            while k < len(intervals) and intervals[k][1] + 1 == i:

                l, r = intervals[k]

                if dp[l] + 1 > dp[i]:
                    dp[i] = dp[l] + 1
                    parent[i] = l
                    choice[i] = (l, r)

                k += 1

        # 4. traceback
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