# TC:O(nlogM) M為數值 SC:O(1)
class Solution:
    def minOperations(self, nums: List[int]) -> List[int]:
        def reverse_lower_bits(x:int, m:int) -> int:
            r = 0
            for _ in range(m):
                r = (r << 1) | (x & 1)
                x >>= 1
            return r

        for i, x in enumerate(nums):
            n = x.bit_length()
            res = inf
            m = n // 2
            left = x >> m # 如果是odd 會保留中位數
            for l in range(left - 1, left + 2):
                real_l = l >> (n % 2)
                right = reverse_lower_bits(real_l, m)
                pal = (l << m) | right
                res = min(res, abs(x - pal))
            nums[i] = res
        return nums

# n <= 5000 的做法
MX = 5000
def check(x) -> bool:
    bin_x = bin(x)[2:]
    return bin_x == bin_x[::-1]
is_valid = [x for x in range(MX + 1) if check(x)]
class Solution:
    def minOperations(self, nums: List[int]) -> List[int]:
        ans = []
        is_valid.append(inf)
        for x in nums:
            l = bisect_right(is_valid, x) - 1
            r = bisect_right(is_valid, x)
            ans.append(min(x - is_valid[l], is_valid[r] - x))
        return ans

class Solution:
    def minOperations(self, nums: List[int]) -> List[int]:
        def is_palindrome(s: str) -> bool:
            return s == s[::-1]
        
        def count_ops(n: int) -> int:
            if n == 0:
                return 0
            s = bin(n)[2:]
            if is_palindrome(s):
                return 0
            
            up = n + 1
            ops_up = 1
            while True:
                if is_palindrome(bin(up)[2:]):
                    break
                up += 1
                ops_up += 1
            
            down = n - 1
            ops_down = 1
            while down >= 0:
                if is_palindrome(bin(down)[2:]):
                    break
                down -= 1
                ops_down += 1
                if ops_down > ops_up:
                    ops_down = inf
                    break
            
            return min(ops_up, ops_down)
        
        return [count_ops(x) for x in nums]
