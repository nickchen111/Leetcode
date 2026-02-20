class Solution:
    def makeLargestSpecial(self, s: str) -> str:
        if len(s) <= 2:
            return s

        substrings = []
        diff = 0
        start = 0
        for i, ch in enumerate(s):
            if ch == '1':
                diff += 1
            else:
                diff -= 1
                if diff == 0:
                    substrings.append("1" + self.makeLargestSpecial(s[start + 1: i]) + "0")
                    start = i + 1

        substrings.sort(reverse=True)
        return ''.join(substrings)