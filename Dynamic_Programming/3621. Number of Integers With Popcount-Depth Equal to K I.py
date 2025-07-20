# TC:O(2 * BL * C * 2) BL : binary length mx = 50, C = 選擇多少個1-bit mx = 50 SC:O(2 * BL * C) 
def compute_popcount_depth():
    depth_map = {}
    for i in range(1, 50): # 2 ^ 50次方內
        x = i
        d = 0
        while x != 1:
            x = bin(x).count("1")
            d += 1
        depth_map[i] = d
    return depth_map
depth_map = compute_popcount_depth()

depth_count = defaultdict(list)
for bits in range(1, 50):
    if depth_map.get(bits) is not None:
        depth_count[depth_map[bits] + 1].append(bits)  # depth starts from 1
class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        if k == 0:
            return 1

        bin_n = bin(n)[2:]
        #print(bin(n))
        L = len(bin_n)
        
        @cache
        def dp(pos: int, ones: int, tight: bool) -> int:
            if pos == L:
                return 1 if ones in depth_count[k] else 0
            res = 0
            limit = int(bin_n[pos]) if tight else 1
            for digit in range(0, limit + 1):
                res += dp(pos + 1, ones + digit, tight and (digit == limit))
            return res
        return dp(0, 0, True) - (1 if k == 1 else 0)
