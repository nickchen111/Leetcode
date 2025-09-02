class Solution:
    def numberOfPairs(self, points: List[List[int]]) -> int:
        points.sort(key=lambda x: (-x[1], x[0]))
        ans = 0
        for i, (px, _) in enumerate(points):
            maxPx = inf
            maxPy = inf
            for j in range(i + 1, len(points)):
                npx, npy = points[j][0], points[j][1]
                if npx < maxPx and npx >= px and npy < maxPy:
                    maxPx = npx
                    minPy = npy
                    ans += 1
        return ans