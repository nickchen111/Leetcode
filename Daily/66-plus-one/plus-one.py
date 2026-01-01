class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        ans = []
        num = 1
        i = len(digits) - 1
        while i >= 0:
            num, mod = divmod(digits[i] + num, 10)
            ans.append(mod)
            i -= 1
        return ([1] if num else []) + ans[::-1]