# TC:O(n * M ^ n) M 為 6 n = 1 + 2 + 3 + .. 6 SC:O(n * M ^ n)
class Solution:
    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:
        mp = defaultdict(list)
        for allow in allowed:
            mp[allow[:2]].append(allow[2])
        n = len(bottom)
        pyramid = [[''] * (i + 1) for i in range(n)]
        pyramid[-1] = bottom
        vis = set()
        def dfs(i:int, j:int) -> bool:
            if i < 0:
                return True
            if j == i + 1:
                row = ''.join(pyramid[i])
                if row in vis:
                    return False
                vis.add(row)
                return dfs(i - 1, 0)
            for top in mp[pyramid[i + 1][j] + pyramid[i + 1][j + 1]]:
                pyramid[i][j] = top
                if dfs(i, j + 1):
                    return True
            return False

        return dfs(n - 2, 0)
