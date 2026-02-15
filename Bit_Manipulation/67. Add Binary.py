# TC:O(max(n, m)) SC:O(max(n, m))
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        i = len(a) - 1
        j = len(b) - 1
        carry = 0
        ans = []
        while i >= 0 or j >= 0 or carry:
            # 計算目前的數字
            total = carry
            if i >= 0:
                total += ord(a[i]) - ord('0')
                i -= 1
            if j >= 0:
                total += ord(b[j]) - ord('0')
                j -= 1
            ans.append(str(total & 1))
            carry = total >> 1
        return "".join(reversed(ans))
