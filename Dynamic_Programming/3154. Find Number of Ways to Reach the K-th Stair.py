# DP TC:O(lgk * lgk * 2) SC:O(lg k * lg k * 2)
class Solution:
    def waysToReachStair(self, k: int) -> int:
        '''
        init: pos = 1, jump = 0
        每次可以做的操作是 往下走一階 但不能連續用 or  < 0 
        或者可以選擇走 i + 2 ^ jump，然後j + 1
        問說有多少種方式可以走到 k 的位置
        因為每個狀態如果都包含進來就可以讓當下狀態的結果有唯一性 所以可以考慮dfs + memo 的dp
        dfs (i, j, choose) 這樣設計
        每次都可能會走 2^n 次方 所以可以假設我可以用lgk的次數走到該位置，也可能往前走，但畢竟限制往回走次數不能連續
        這個間接的指明不可能倒退走，所以就算往前都倒退走 那也就是 lg(k + lgk) 大概這麼多步
        '''
        @cache 
        def dfs(i:int, j:int, choose:bool) -> int:
            if i > k + 1:
                return 0
            ans = 1 if i == k else 0
            if not choose and i - 1 >= 0:
                ans += dfs(i - 1, j, True)
            ans += dfs(i + (1 << j), j + 1, False)
            return ans
        return dfs(1, 0, False)

# 組合數學 TC: O(1) SC:O(1)
class Solution:
    def waysToReachStair(self, k: int) -> int:
        '''
        init: pos = 1, jump = 0
        每次可以做的操作是 往下走一階 但不能連續用 or  < 0 
        或者可以選擇走 i + 2 ^ jump，然後j + 1
        問說有多少種方式可以走到 k 的位置
        因為每個狀態如果都包含進來就可以讓當下狀態的結果有唯一性 所以可以考慮dfs + memo 的dp
        dfs (i, j, choose) 這樣設計
        每次都可能會走 2^n 次方 所以可以假設我可以用lgk的次數走到該位置，也可能往前走，但畢竟限制往回走次數不能連續
        這個間接的指明不可能倒退走，所以就算往前都倒退走 那也就是 lg(k + lgk) 大概這麼多步
        '''
        ans = 0
        start = (max(0,k-1)).bit_length()
        for j in range(start, 30):
            m = (1 << j) - k
            if m > j + 1:
                break
            if m <= j + 1:
                ans += comb(j + 1, m) #這玩意可以預處理 用遞推式 C n取m = Cn-1 取 m -1 + c n-1 取 m  選or不選去思考得出
        return ans
