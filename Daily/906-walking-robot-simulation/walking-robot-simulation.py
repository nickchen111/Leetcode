class Solution:
    def robotSim(self, commands: List[int], obstacles: List[List[int]]) -> int:
        dirs = (0,1), (1,0), (0,-1), (-1,0)
        dir = 0
        MOD = 4
        obs = set(map(tuple, obstacles))
        ans = x = y = 0
        for c in commands:
            if c == -1: # turn right
                dir = (dir + 1) % MOD
            elif c == -2: # turn left
                dir = (dir - 1 + MOD) % MOD
            else:
                # 一步一步走 否則可能超過obstacle
                for i in range(1, c + 1):
                    nx, ny = x + dirs[dir][0], y + dirs[dir][1]
                    if (nx, ny) in obs:
                        break
                    x, y = nx, ny
            ans = max(ans, x * x + y * y)
        return ans