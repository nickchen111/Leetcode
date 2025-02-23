# 組合數學解法
class Solution:
    def getRow(self, rowIndex: int) -> List[int]:
        fac = [0] * (rowIndex+1)
        fac[0] = 1
        for i in range(1, rowIndex+1):
            fac[i] = fac[i-1] * i

        inv = [0] * (rowIndex+1)
        inv[-1] = pow(fac[-1], -1)
        for i in range(rowIndex-1, -1, -1):
            inv[i] = inv[i+1] * (i+1)
            
        c = [round(fac[rowIndex] * inv[i] * inv[rowIndex-i]) for i in range(rowIndex+1)]

        return c
