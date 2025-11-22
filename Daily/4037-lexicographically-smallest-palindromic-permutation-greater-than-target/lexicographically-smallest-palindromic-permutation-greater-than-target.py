class Solution:
    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        n = len(s)

        # 先確認是否可以構成回文串
        left = Counter(s)

        def valid() -> bool:
            return all(c >= 0 for c in left.values())
        min_ch = ''
        for ch, c in left.items():
            if c % 2 == 0:
                continue
            if min_ch:
                return ""
            min_ch = ch
            left[ch] -= 1
        # 確認是否可以用特殊情況前半段一樣構成回文串並且比target大
        for i, b  in enumerate(target[: n//2]):
            left[b] -= 2
        if valid():
            left_s = target[:n//2]
            right_s = min_ch + left_s[::-1]
            if right_s > target[n//2:]:
                return left_s + right_s
        # 貪心從後段開始判斷是否可以構造出
        for i in range(n // 2 - 1, -1, -1):
            b = target[i]
            left[b] += 2
            if not valid():
                continue
            for j in range(ord(b) - ord('a') + 1, 26):
                ch = ascii_lowercase[j]
                if left[ch] == 0: # 沒有這個字母可用
                    continue
                left[ch] -= 2
                ans = list(target[:i+1])
                ans[i] = ch
                for ch in ascii_lowercase:
                    ans.extend(ch * (left[ch] // 2))
                right_s = ans[::-1]
                ans.append(min_ch)
                ans += right_s
                return ''.join(ans)
        return ""





