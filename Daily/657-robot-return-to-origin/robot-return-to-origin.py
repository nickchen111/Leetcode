class Solution:
    def judgeCircle(self, moves: str) -> bool:
        x = y = 0
        for dir in moves:
            if dir in {'L', 'R'}:
                x += 1 if dir == 'R' else -1
            if dir in {'U', 'D'}:
                y += 1 if dir == 'U' else -1
        return x == 0 and y == 0