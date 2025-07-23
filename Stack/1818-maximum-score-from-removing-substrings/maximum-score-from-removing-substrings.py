class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        if x < y:
            s = s[::-1]
            x, y = y, x
        first, second = 'ab', 'ba'
        
        def remove_pair(s: str, pattern: str, score: int) -> tuple[str, int]:
            stack = []
            total = 0
            for ch in s:
                if stack and stack[-1] + ch == pattern:
                    stack.pop()
                    total += score
                else:
                    stack.append(ch)
            return ''.join(stack), total

        remain, gain1 = remove_pair(s, first, x)
        _, gain2 = remove_pair(remain, second, y)
        return gain1 + gain2
