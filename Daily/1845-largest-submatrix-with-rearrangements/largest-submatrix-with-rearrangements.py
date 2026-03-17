class Solution:
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        n = len(matrix[0])
        heights = [0] * n
        idx = list(range(n))
        ans = 0

        for row in matrix:
            zeros = []
            non_zeros = []
            for j in idx:
                if row[j] == 0:
                    heights[j] = 0
                    zeros.append(j)
                else:
                    heights[j] += 1
                    non_zeros.append(j)
            idx = zeros + non_zeros 
            for i in range(len(zeros), n):
                ans = max(ans, (n - i) * heights[idx[i]])

        return ans