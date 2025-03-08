# TC:O(n) SC:O(1)
class Solution:
    def minimumRecolors(self, blocks: str, k: int) -> int:
        n, i, ans, cnt = len(blocks), 0, inf, 0
        for j in range(n):
            cnt += 1 if blocks[j] == 'W' else 0
            if j - i + 1 == k:
                ans = min(ans, cnt)
                cnt -= 1 if blocks[i] == 'W' else 0
                i += 1
        return ans
