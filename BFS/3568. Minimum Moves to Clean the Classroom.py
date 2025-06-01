# TC:O(4 * m * n * 2 ^ k * e) k = 10, e = 50 SC:O((m * n * 2 ^ k * e)
class Solution:
    def minMoves(self, classroom: List[str], energy: int) -> int:
        m, n = len(classroom), len(classroom[0])
        litter = []
        for i in range(m):
            for j in range(n):
                if classroom[i][j] == 'S':
                    sx, sy = i, j
                elif classroom[i][j] == 'L':
                    litter.append((i, j))
        litter_map = {(x, y): i for i, (x, y) in enumerate(litter)}
        target_mask = (1 << len(litter)) - 1
        dirs = [(-1,0), (1,0), (0,-1), (0,1)]
        # visited: (x, y, mask) -> energy，儲存到達這狀態時剩餘能量的最大值
        visited = dict()
        q = deque()
        q.append((sx, sy, target_mask, energy))  # x, y, mask, en
        visited[(sx, sy, target_mask)] = energy
        steps = 0
        while q:
            sz = len(q)
            for i in range(sz):
                x, y, mask, en = q.popleft()
                if mask == 0:
                    return steps
                # if mask == target_mask:
                #     return steps
                for dx, dy in dirs:
                    nx, ny = x + dx, y + dy
                    if not (0 <= nx < m and 0 <= ny < n) or classroom[nx][ny] == 'X' or en - 1 < 0:
                        continue
                    nen = en - 1 if classroom[nx][ny] != 'R' else energy
                    nmask = mask if classroom[nx][ny] != 'L' else mask & ~(1 << litter_map[(nx, ny)]) # nmask |= (1 << idx)
                    key = (nx, ny, nmask)
                    # 如果這個狀態以前來過，而且剩下能量比這次多，就不擴展
                    if key in visited and visited[key] >= nen:
                        continue
                    visited[key] = nen
                    q.append((nx, ny, nmask, nen))
            steps += 1
        return -1
