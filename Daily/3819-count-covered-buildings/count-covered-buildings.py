class Solution:
    def countCoveredBuildings(self, n: int, buildings: List[List[int]]) -> int:
        x = defaultdict(list)
        y = defaultdict(list)
        for b1, b2 in buildings:
            x[b1].append(b2)
            y[b2].append(b1)
        for l,v in x.items():
            v.sort()
        for l,v in y.items():
            v.sort()
        ans = 0
        for b1, b2 in buildings:
            if x[b1][0] < b2 < x[b1][-1] and y[b2][0] < b1 < y[b2][-1]:
                ans += 1
        return ans
            