# TC:O(m * n) SC:O(1)
class Solution:
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        m, n = len(mat), len(mat[0])
        ans = []
        for k in range(m + n - 1):
            # i + j = k
            min_j = max(k - m + 1, 0)
            max_j = min(k, n - 1)
            if k % 2 == 0:
                for j in range(min_j, max_j + 1):
                    ans.append(mat[k - j][j])
            else:
                for j in range(max_j, min_j - 1, -1):
                    ans.append(mat[k - j][j])
        return ans
