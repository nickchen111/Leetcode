# TC:O(n * 2 * 2 * U * n * 10) n 最多 4, U為數字元素總和最大值 max 27 SC:O(n * 2 * 2 * U * n)
class Solution:
    def countSymmetricIntegers(self, low: int, high: int) -> int:
        '''
        Another Digit DP 需要前後段總和相同
        sum 前段加法 後段減法
        '''
        def countIntegers(num:int) -> int:
            # 轉數字轉成列表以便存取
            arr = list(map(int, str(num)))
            n = len(arr)
            @cache
            def dfs(i:int, is_num:bool, is_limit:bool, sum:int, l:int) -> int:
                if i == n:
                    return 1 if sum == 0 and is_num else 0
                ans = 0
                if not is_num:
                    ans = dfs(i+1, False, False, sum, l)
                if (n - i) % 2 == 0 or l != 0:
                    down = 0 if is_num else 1
                    up = 9 if not is_limit else arr[i]
                    for j in range(down, up + 1):
                        ans = ans + (dfs(i+1, True, is_limit and j == up, sum - j, l + 1) if l + 1 > (l + n - i) // 2  else dfs(i+1, True, is_limit and j == up, sum + j, l + 1))
                return ans
            return dfs(0, False, True, 0, 0)   
        return countIntegers(high) - countIntegers(low - 1)
            
