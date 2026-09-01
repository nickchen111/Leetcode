class Solution:
    def minMoves(self, classroom: List[str], energy: int) -> int:
        m, n = len(classroom), len(classroom[0])

        mp = {}
        sx = sy = -1
        cnt = 0

        for i in range(m):
            for j in range(n):
                if classroom[i][j] == 'L':
                    mp[(i, j)] = cnt
                    cnt += 1
                elif classroom[i][j] == 'S':
                    sx, sy = i, j
        if cnt == 0:
            return 0
        target = (1 << cnt) - 1

        q = deque([(sx, sy, energy, 0)])

        # (x, y, energy, mask)
        vis = {(sx, sy, energy, 0)}

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

                    state = (nx, ny, ne, nmask)

                    if state not in vis:
                        vis.add(state)
                        q.append(state)

            step += 1

        return -1