max = lambda a, b: a if a > b else b
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        '''
        也就是只能有兩種數字 要選subarray 返回最長的subarray -> 滑窗 越短越合法
        '''
        n = len(fruits)
        mx = 0
        for x in fruits:
            mx = max(mx, x)
        type_arr = [0] * (mx + 1)
        i = ans = cnt = 0
        for j, x in enumerate(fruits):
            if type_arr[x] == 0:
                cnt += 1
            type_arr[x] += 1
            while cnt > 2:
                type_arr[fruits[i]] -= 1
                if type_arr[fruits[i]] == 0:
                    cnt -= 1
                i += 1
            ans = max(ans, j - i + 1)
        return ans
            


