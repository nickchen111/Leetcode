class Solution:
    def minimumBoxes(self, apple: List[int], capacity: List[int]) -> int:
        capacity.sort(reverse=True)
        tot = sum(apple)
        cur = 0
        for i, x in enumerate(capacity):
            cur += x
            if cur >= tot:
                return i + 1
        return -1