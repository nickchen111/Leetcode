class Solution:
    def countCollisions(self, directions: str) -> int:
        n = len(directions)
        cnt = ans = 0
        obs = False
        for dir in directions:
            if dir == 'L':
                if obs:
                    ans += cnt + 1
                    cnt = 0
            elif dir == 'R':
                cnt += 1
                obs = True
            else:
                ans += cnt
                cnt = 0
                obs = True
        return ans