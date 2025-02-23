# O(n)
N = n - 1  # 計算楊輝三角第 N-1 行
coef = [1]  # 用來存儲 C(N-1, k)
prev = 1

# 計算楊輝三角係數
for k in range(1, N + 1):
    next_val = prev * (N - k + 1) // k
    coef.append(next_val)
    prev = next_val

# 公式解
MX = 34
c = [[1] * (i + 1) for i in range(MX)]
for i in range(2, MX):
    for j in range(1, i):
        # 左上方的数 + 正上方的数
        c[i][j] = c[i - 1][j - 1] + c[i - 1][j]

class Solution:
    def getRow(self, rowIndex: int) -> List[int]:
        return c[rowIndex]

# 組合數學解
class Solution:
    def getRow(self, rowIndex: int) -> List[int]:
        return [comb(rowIndex, i) for i in range(rowIndex+1)]

#組合數學 加上 逆元
n = 10 # 假設要求的項的index是下標10 其實代表會有11項
MOD = 1000000007
fac = [0] * (n+1)
fac[0] = 1
for i in range(1, n+1):
    fac[i] = fac[i-1] * i
inv = [0] * (n+1)
inv[-1] = pow(fac[-1], -1)
for i in range(n-1, -1, -1):
    inv[i] = inv[i+1] * (i+1)
c = [fac[n] * inv[i] * inv[n-i] for i in range(n+1)]    
