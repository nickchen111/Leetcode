MOD = 1_000_000_007
MX = 31

fac = [0] * MX  # fac[i] = i!
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % MOD

inv = [0] * MX  # inv_f[i] = i!^-1
inv[-1] = pow(fac[-1], -1, MOD)
for i in range(MX - 1, 0, -1):
    inv[i - 1] = inv[i] * i % MOD

class Solution:
    def magicalSum(self, m: int, k: int, nums: List[int]) -> int:
        '''
        1. 公式推導 組合數學
        如果沒有 2 ^ seq[i] 總和要滿足set bit條件 
        這題就是 從0 枚舉到 n - 1 看會有哪些組合? 然後去重
        例如 a[0]^3 * a[1]^2 / (3! * 2!) 會有這種選法，這個部分會需要用到逆元，這題也要求你要對答案取模
        並且這裡的a[0] a[1] 可以理解成類似貢獻法，我取了3個0 2個1可以對答案有多少貢獻，由於他可以任意排列組合，所以公式裡會有一個m!代表任意排列狀態
        接著再搭上逆元去重
        2. 狀態設計(DP)
        但這題需要你去枚舉加總的結果bit數量 會發現 2^50 太大了...放在狀態裡面很難，所以最難的點是想到要將總和S的後面不會影響到的數字消除掉
        先將它統計起來，瞬間他每回最大的狀態就只會有 m / 2個
        所以回首這題狀態需要以下四項就可以確定每個狀態無後效性
        a. 目前用到哪個數字
        b. 目前還剩下多少個數字要選
        c. 目前選擇的總和
        d. 目前還剩餘多少個bit 需要從當前選擇獲取
        '''
        n = len(nums)
        pow_v = [[1] * (m + 1) for _ in range(n)] # 每個數字的次方會是多少
        for i in range(n):
            for j in range(1, m + 1):
                pow_v[i][j] = pow_v[i][j - 1] * nums[i] % MOD
        @cache
        def dfs(i:int, left_m:int, s:int, left_k:int) -> int:
            c1 = s.bit_count()
            if c1 + left_m < left_k:  # 剪枝
                return 0
            if i == n:
                return 1 if left_m == 0 and c1 == left_k else 0
            ans = 0
            for j in range(left_m + 1): # 目前要選幾個當前數字
                bit = (s + j) & 1 # 取低位判斷後續右移s後是否會多bit
                if bit <= left_k:
                    r = dfs(i + 1, left_m - j, (s + j) >> 1, left_k - bit)
                    ans = (ans + r * pow_v[i][j] % MOD * inv[j]) % MOD
            return ans
        return dfs(0, m, 0, k) * fac[m] % MOD
                 
            