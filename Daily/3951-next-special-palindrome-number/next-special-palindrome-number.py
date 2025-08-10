# 預處理合法 (left, center)
valid_configs = []
for mask in range(1, 1 << 9):
    chosen = []
    S = 0
    odd_count = 0
    for i in range(9):
        if (mask >> i) & 1:
            d = i + 1
            chosen.append(d)
            S += d
            if d % 2 == 1:
                odd_count += 1
    if S > 16 or odd_count > 1:
        continue
    left = []
    center = None
    for d in chosen:
        left.extend([d] * (d // 2))
        if d % 2 == 1:
            center = d
    left.sort()
    valid_configs.append((left, center, S))
class Solution:
    def specialPalindrome(self, n: int) -> int:
        s = str(n)
        specials = []
        def backtrack(left, center):
            used = [False] * len(left)
            path = []

            def dfs():
                if len(path) == len(left):
                    half = tuple(path)
                    if center is None:
                        full = half + half[::-1]
                    else:
                        full = half + (center,) + half[::-1]
                    cur = int("".join(map(str, full)))
                    if cur > n:
                        specials.append(cur)
                    return
                for i in range(len(left)):
                    if used[i]:
                        continue
                    if i > 0 and left[i] == left[i - 1] and not used[i - 1]:
                        continue
                    used[i] = True
                    path.append(left[i])
                    dfs()
                    path.pop()
                    used[i] = False

            if not left:
                if center and center > n:
                    specials.append(center)
            else:
                dfs()

        for left, center, length in valid_configs:
            if length != len(s) and length != len(s) + 1:
                continue
            backtrack(left, center)

        specials.sort()
        idx = bisect.bisect_right(specials, n)
        return specials[idx]
