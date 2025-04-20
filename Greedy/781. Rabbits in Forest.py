# TC:O(n) SC:O(n)
class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        return sum((c + x) // (x + 1) * (x + 1) for x, c in Counter(answers).items())
