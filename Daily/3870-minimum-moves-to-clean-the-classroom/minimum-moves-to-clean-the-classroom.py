class Solution:
    def minMoves(self, classroom: List[str], energy: int) -> int:
        m, n = len(classroom), len(classroom[0])

        mp = {}
        sx = sy = -1
        cnt = 0

        for i in range(m):
            for j in range(n):
                c = classroom[i][j]

                if c == 'L':
                    mp[(i, j)] = cnt
                    cnt += 1
                elif c == 'S':
                    sx, sy = i, j

        if cnt == 0:
            return 0

        target = (1 << cnt) - 1

        # best[x][y][mask] = 到過這個 state 時的最大 energy
        best = [
            [[-1] * (1 << cnt) for _ in range(n)]
            for _ in range(m)
        ]

        q = deque()
        q.append((sx, sy, energy, 0))
        best[sx][sy][0] = energy

        dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]

        step = 0

        while q:
            for _ in range(len(q)):
                x, y, e, mask = q.popleft()

                if mask == target:
                    return step

                if e == 0:
                    continue

                for dx, dy in dirs:
                    nx, ny = x + dx, y + dy

                    if not (0 <= nx < m and 0 <= ny < n):
                        continue

                    if classroom[nx][ny] == 'X':
                        continue

                    ne = e - 1
                    nmask = mask

                    if classroom[nx][ny] == 'L':
                        nmask |= 1 << mp[(nx, ny)]

                    if classroom[nx][ny] == 'R':
                        ne = energy

                    if ne <= best[nx][ny][nmask]:
                        continue

                    best[nx][ny][nmask] = ne
                    q.append((nx, ny, ne, nmask))

            step += 1

        return -1