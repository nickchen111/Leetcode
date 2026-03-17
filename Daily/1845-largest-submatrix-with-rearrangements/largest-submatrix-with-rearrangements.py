class Solution:
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        ans = 0
        arr = [0] * n # 在 j index 有多少的高度
        for row in matrix:
            height = [] # 有哪些高度
            for j, v in enumerate(row):
                if v:
                    arr[j] += 1
                    height.append(arr[j])
                else:
                    arr[j] = 0
            height.sort()
            l = len(height)
            for i, h in enumerate(height):
                ans = max(ans, h * (l - i))
        return ans
                