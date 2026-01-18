# TC:O(n) SC:O(1)
class Solution:
    def vowelConsonantScore(self, s: str) -> int:
        v = c = 0
        for ch in s:
            if not ch.isalpha():
                continue
            if ch in "aeiou":
                v += 1
            else:
                c += 1
        return v // c if c else 0
