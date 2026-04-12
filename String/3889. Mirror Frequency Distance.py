# TC:O(n) SC:O(M) M為字元種類數量
class Solution:
    def mirrorFrequency(self, s: str) -> int:
        freq = Counter(s)
        unique_chars = freq.keys()
        processed = set()
        ans = 0
        
        for c in unique_chars:
            if c in processed:
                continue
            if 'a' <= c <= 'z':
                m = chr(ord('a') + ord('z') - ord(c))
            else:
                m = chr(ord('0') + ord('9') - ord(c))
            freq_c = freq[c]
            freq_m = freq.get(m, 0)
            ans += abs(freq_c - freq_m)
            processed.add(c)
            processed.add(m)
        return ans
