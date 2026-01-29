class Solution:
    def minimumCost(self, source: str, target: str, original: List[str], changed: List[str], cost: List[int]) -> int:
        n = len(source)
        minCost = [[inf] * 26 for _ in range(26)]
        for ori, ch, c in zip(original, changed, cost):
            a = ord(ori) - ord('a')
            b = ord(ch) - ord('a')
            minCost[a][b] = min(minCost[a][b], c)
        for i in range(26):
            minCost[i][i] = 0
        for k in range(26):
            for i in range(26):
                for j in range(26):
                    minCost[i][j] = min(minCost[i][j], minCost[i][k] + minCost[k][j])
        ans = 0
        for s, t in zip(source, target):
            if s != t:
                ans += minCost[ord(s) - ord('a')][ord(t) - ord('a')]
        return ans if ans != inf else -1

        