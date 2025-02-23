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
