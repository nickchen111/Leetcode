class Solution:
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:
        k %= len(mat[0])
        return k == 0 or all(row == row[k:] + row[:k] for row in mat)
