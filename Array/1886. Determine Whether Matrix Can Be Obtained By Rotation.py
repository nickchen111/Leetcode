# TC:O(mn) SC:O(1)
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        n = len(matrix)
        for i, row in enumerate(matrix):
            for j in range(i + 1, n):
                row[j], matrix[j][i] = matrix[j][i], row[j]
            row.reverse()

    def findRotation(self, mat: List[List[int]], target: List[List[int]]) -> bool:
        for _ in range(4):
            if mat == target:
                return True
            self.rotate(mat)
        return False
