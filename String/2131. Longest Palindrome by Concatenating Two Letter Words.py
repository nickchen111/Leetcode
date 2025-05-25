# TC:O(n * m) SC:O(n * m) m 為字串長度
class Solution:
    def longestPalindrome(self, words: List[str]) -> int:
        count = Counter(words)
        length = 0
        has_center = False
        
        for word in list(count.keys()):
            rev = word[::-1]
            if word == rev:
                pairs = count[word] // 2
                length += pairs * 4
                count[word] -= pairs * 2
                if count[word] > 0:
                    has_center = True
            else:
                if rev in count:
                    pair_count = min(count[word], count[rev])
                    length += pair_count * 4
                    count[word] -= pair_count
                    count[rev] -= pair_count
        
        if has_center:
            length += 2
        return length
