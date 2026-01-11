class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        st = [-1]
        ans = 0
        for right, h in enumerate(heights):
            while len(st) > 1 and heights[st[-1]] >= h:
                i = st.pop()
                w = right - st[-1] - 1
                ans = max(ans, heights[i] * w)
            st.append(right)
        return ans
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        '''
        stack 從低到高
        '''
        n = len(matrix[0])
        heights = [0] * (n + 1)
        ans = 0
        for m in matrix:
            for j, c in enumerate(m):
                if c == '0':
                    heights[j] = 0
                else:
                    heights[j] += 1
            ans = max(ans, self.largestRectangleArea(heights))
        return ans


