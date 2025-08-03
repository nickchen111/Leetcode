class Solution:
    def maxTotalFruits(self, fruits: List[List[int]], startPos: int, k: int) -> int:
        '''
        分三種情況討論
        1. 只拿左
        2. 只拿右
        3. 先去左再去右 or 先去右再去左
        '''
        n = len(fruits)
        # right_start = bisect_right(fruits, startPos, key=lambda x: x[0])
        right_end = bisect_right(fruits, startPos + k, key=lambda x: x[0])
        # cur_sum = 0
        # for i in range(right_start, right_end):
        #     cur_sum += fruits[i][1]
        # ans = cur_sum
        ans = 0
        cur_sum = 0
        left_start = bisect_left(fruits, max(0, startPos - k), key=lambda x: x[0])
        left_end = bisect_right(fruits, startPos, key=lambda x: x[0])
        for i in range(left_start, left_end):
            cur_sum += fruits[i][1]
        ans = max(ans, cur_sum)
        
        i = left_start
        # print(left_start, left_end, right_start, right_end)
        for j in range(left_end, right_end):
            cur_sum += fruits[j][1]
            while fruits[j][0] + startPos - fruits[i][0] * 2 > k and fruits[j][0] * 2 - startPos - fruits[i][0] > k:
                cur_sum -= fruits[i][1]
                i += 1
            ans = max(ans, cur_sum)
        return ans
