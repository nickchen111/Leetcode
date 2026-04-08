# Two Pointer 可以將時間優化到n * 360左右 也就是在嘗試放一個數字的時候對他前面的那段做前綴和 後續用雙指針不斷往後走
# prefix: TC:O(nU) SC:O(U)
MOD = 10**9 + 7
MAX_V = 5000
def get_digit_sum(num:int) -> int:
    s = 0
    while num:
        s += num % 10
        num //= 10
    return s
d_sums = [get_digit_sum(i) for i in range(MAX_V + 1)]
class Solution:
    def countArrays(self, digitSum: list[int]) -> int:
        '''
        數字要包含在5000內, 非遞減, 所有個別數字拆解加總等於 digitsum[i]
        4999 = 31 如果digitsum裡面有數字超過31那就不可能
        可以先預處理每個數字加總的可能性有哪些 
        例如 0, 1, 2, 3 會可能是哪些數字加總出來
        key: 0 ~ 31 value 就是 0 ~ 5000
        然後做DP
        '''
        if any(s > 31 for s in digitSum):
            return 0
        dp = [0] * (MAX_V + 1)
        target0 = digitSum[0]
        for v in range(MAX_V + 1):
            if d_sums[v] == target0:
                dp[v] = 1
        
        for i in range(1, len(digitSum)):
            target = digitSum[i]
            new_dp = [0] * (MAX_V + 1)
            curr_sum = 0
            for v in range(MAX_V + 1):
                curr_sum = (curr_sum + dp[v]) % MOD
                if d_sums[v] == target:
                    new_dp[v] = curr_sum
            dp = new_dp
        return sum(dp) % MOD
