# TC:O(n) SC:O(n)
class Solution:
    def distinctPoints(self, s: str, k: int) -> int:
        move = {
            'U': (1, 0),
            'D': (-1, 0),
            'R': (0, 1),
            'L': (0, -1),
        }
        
        st = set()
        tmp = [0, 0]
        i = 0
        
        for j, ch in enumerate(s):
            dx, dy = move[ch]
            tmp[0] += dx
            tmp[1] += dy

            if j - i + 1 == k:
                st.add(tuple(tmp))
                dx, dy = move[s[i]]
                tmp[0] -= dx
                tmp[1] -= dy
                i += 1
        return len(st)
