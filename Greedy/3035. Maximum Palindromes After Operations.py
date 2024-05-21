#3035. Maximum Palindromes After Operations

#TC:O(nlgn+n*m) SC:O(n)
class Solution:
    def maxPalindromesAfterOperations(self, words: List[str]) -> int:
        cnt = Counter()
        for w in words:
            cnt += Counter(w)
        left = sum(c//2 for c in cnt.values())

        words.sort(key = len)
        res = 0
        for w in words:
            m = len(w) // 2
            if left < m : 
                break
            left -= m
            res += 1
        return res
