class Solution:
    def numSpecial(self, mat: List[List[int]]) -> int:
        ans = 0
        for row in mat:
            if sum(row) != 1:
                continue
            j = row.index(1)
            if sum(row[j] for row in mat) == 1:
                ans += 1
        return ans