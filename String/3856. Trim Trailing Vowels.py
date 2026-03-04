# TC:O(n) SC:O(1)
class Solution:
    def trimTrailingVowels(self, s: str) -> str:
        for i in range(len(s) - 1, -1, -1):
            if s[i] not in {'a', 'e', 'i', 'o', 'u'}:
                return s[0:i + 1]
        return ""
