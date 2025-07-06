# TC:O(logn) SC:O(logn) 
import numpy as np
class Solution:
    def concatHex36(self, n: int) -> str:
        return np.base_repr(n * n, 16) + np.base_repr(n * n * n, 36)
        def to_base(num:int, base:int) -> str:
            digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            if num == 0:
                return "0"
            ans = []
            while num > 0:
                ans.append(digits[num % base])
                num //= base
            return ''.join(reversed(ans))
        s = to_base(n * n, 16)
        t = to_base(n * n * n, 36)
        return s + t
