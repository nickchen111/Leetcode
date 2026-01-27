# TC:O(W) W為二進制最大值  SC:O(1)
class Solution:
    def nthSmallest(self, n: int, k: int) -> int:
        ans = 0
        for i in range(49, -1, -1):
            c = comb(i, k)
            if n > c: # 代表這個位置要填1
                n -= c
                ans |= 1 << i
                k -= 1
                if k == 0:
                    return ans
        return ans


# 老實二分
MX = 50
C = [[0] * MX for _ in range(MX)]
for i in range(MX):
    C[i][0] = 1
    for j in range(1, i + 1):
        C[i][j] = C[i-1][j-1] + C[i-1][j] # 就是最後一個數 選 or 不選 
class Solution:
    def nthSmallest(self, n: int, k: int) -> int:
        def countWithKOnes(x:int, k:int) -> int:
            res = 0
            count_one = 0
            max_bit = x.bit_length()
            for i in range(max_bit - 1, -1, -1):
                if (x >> i) & 1:
                    k_left = k - count_one
                    if 0 <= k_left <= i:
                        res += C[i][k_left]
                    count_one += 1
            
            if count_one == k:
                res += 1
            return res

        low = 1
        high = (1 << 50) - 1
        while low < high:
            mid = (low + high) // 2
            if countWithKOnes(mid, k) >= n:
                high = mid
            else:
                low = mid + 1
        return low
