class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        return min((c for c in letters if c > target), default=letters[0])