class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        if numRows == 1:
            return [[1]]
        ans = [[1], [1, 1]]
        if numRows == 2:
            return ans
        for i in range(2, numRows):
            tmp = [ans[-1][0]]
            for j in range(1, len(ans[-1])):
                tmp.append(ans[-1][j] + ans[-1][j - 1])
            tmp.append(ans[-1][-1])
            ans.append(tmp)
        return ans