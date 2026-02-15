# TC:O(nk) SC:O(nk)
class Solution:
    def prefixConnected(self, words: List[str], k: int) -> int:
        mp = defaultdict(int)
        for word in words:
            if len(word) < k:
                continue
            mp[word[:k]] += 1
        return sum(1 if v > 1 else 0 for v in mp.values())
