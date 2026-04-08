# Two Pointer 可以將時間優化到n * 360左右 也就是在嘗試放一個數字的時候對他前面的那段做前綴和 後續用雙指針不斷往後走
MOD = 1_000_000_007
MX = 5001
MAX_DIGIT_SUM = 31
sum_to_nums = [[] for _ in range(MAX_DIGIT_SUM + 1)]
dig_sum = [0] * MX
for x in range(MX):
    dig_sum[x] = dig_sum[x // 10] + x % 10
    sum_to_nums[dig_sum[x]].append(x)

class Solution:
    def countArrays(self, digitSum: List[int]) -> int:
        f = [0] * MX  # f[x] 表示以 x 结尾的有效数组的个数
        f[0] = 1
        pre = 0

        for cur in digitSum:
            if cur > MAX_DIGIT_SUM:
                return 0
            a = sum_to_nums[pre]
            j, m = 0, len(a)
            s = 0
            for x in sum_to_nums[cur]:
                # 有效数组的前一个数只要 <= x 就行
                while j < m and a[j] <= x:
                    s += f[a[j]]
                    j += 1
                # s 现在就是以 x 结尾的有效数组的个数
                f[x] = s % MOD
            pre = cur

        return sum(f[x] for x in sum_to_nums[pre]) % MOD
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
