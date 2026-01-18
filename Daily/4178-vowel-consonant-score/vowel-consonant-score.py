class Solution:
    def vowelConsonantScore(self, s: str) -> int:
        v = c = 0
        for ch in s:
            if ch in {'a', 'e', 'i', 'o', 'u'}:
                v += 1
            elif ch != ' ' and not '0' <= ch <= '9':
                c += 1
        return 0 if c == 0 else v // c