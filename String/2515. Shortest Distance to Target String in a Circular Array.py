# TC:O(mn) SC:O(1)
class Solution:
    def closestTarget(self, words: List[str], target: str, startIndex: int) -> int:
        ans = inf
        for i, w in enumerate(words):
            if w == target:
                ans = min(ans, abs(startIndex - i), len(words) - abs(startIndex - i))
        return ans if ans != inf else -1
