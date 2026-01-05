class Solution:
    def maxMatrixSum(self, matrix: List[List[int]]) -> int:
        '''
        就看有多少個neg odd 就選最大的那個不變
        '''
        cnt = ans = 0
        mn = inf
        for i in range(len(matrix)):
            for j in range(len(matrix[i])):
                if matrix[i][j] < 0:
                    cnt += 1
                ans += abs(matrix[i][j])
                mn = min(mn, abs(matrix[i][j]))
        return ans if cnt % 2 == 0 else ans - 2 * mn