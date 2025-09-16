# TC:O(n * M) M 為字串平均長度 SC:O(B) B為禁止字元數量
class Solution:
    def canBeTypedWords(self, text: str, broken: str) -> int:
        brokenKeys = set(broken)
        words = text.split(" ")
        count = 0

        for word in words:
            for c in word:
                if c in brokenKeys:
                    count += 1
                    break

        return len(words) - count
