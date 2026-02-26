class Solution:
    def numSteps(self, s: str) -> int:
        ans = len(s) - 1
        carry = 0
        for i in range(len(s) - 1, 0, -1):
            sum_ = int(s[i]) + carry
            ans += sum_ % 2
            carry = (sum_ + sum_ % 2) // 2
        return ans + carry