# TC:O(L) L為所有字串長度 SC:O(n) n 為字串數量
class Solution:
    def mapWordWeights(self, words, weights):
        res = []
        for word in words:
            tot = sum(weights[ord(c) - ord('a')] for c in word) % 26
            res.append(chr((25 - tot) % 26 + ord('a')))

        return "".join(res)
